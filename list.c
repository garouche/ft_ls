/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:40:38 by garouche          #+#    #+#             */
/*   Updated: 2017/04/22 17:56:19 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*init_ls(void)
{
	t_ls *new;

	if ((new = malloc(sizeof(t_ls))) == NULL)
		exit(EXIT_FAILURE);
	ft_bzero(new, sizeof(t_ls));
	return (new);
}

int		sort(t_ls *buf, t_ls **lst, t_opt *opt)
{
	int i;

	i = 0;
	if (opt->t >= 1)
	{
		if ((i = (*lst)->st.st_mtime - buf->st.st_mtime) == 0)
			if ((i = (*lst)->st.st_mtimespec.tv_nsec -
						buf->st.st_mtimespec.tv_nsec) == 0)
				i = ft_strcmp(buf->path, (*lst)->path);
	}
	else
		i = ft_strcmp(buf->path, (*lst)->path);
	return (opt->r >= 1 ? -i : i);
}

void	sort_ls(t_ls *buf, t_ls **lst, t_opt *opt)
{
	t_ls *ptr;

	ptr = *lst;
	buf->errn = (buf->folder == NULL ? errno : 0);
	errno = 0;
	if (!(*lst)->path)
	{
		free(*lst);
		*lst = buf;
	}
	else if (sort(buf, lst, opt) > 0)
	{
		while (ptr->next && sort(buf, &ptr->next, opt) > 0)
			ptr = ptr->next;
		buf->next = ptr->next;
		ptr->next = buf;
	}
	else
	{
		buf->next = *lst;
		*lst = buf;
	}
}

t_max	*push_lst(t_ls **ptr, t_ls **files, t_opt *opt, char *av)
{
	t_ls			*buf;
	static	t_max	*max = NULL;

	if (!max && opt->l)
		max = ft_memalloc(sizeof(t_max));
	if (!(buf = manage_files_lst(opt, av, av)) || (!max && opt->l))
		exit(EXIT_FAILURE);
	if (opt->l && S_ISLNK(buf->st.st_mode))
	{
		get_max(buf, max);
		sort_ls(buf, files, opt);
	}
	else if ((buf->folder = opendir(buf->path)) || errno == 13)
		sort_ls(buf, ptr, opt);
	else if (errno == 20 || S_ISLNK(buf->st.st_mode))
	{
		opt->l ? get_max(buf, max) : 0;
		sort_ls(buf, files, opt);
	}
	else
	{
		display_name(buf->path, errno, 2);
		free(buf);
	}
	return (max);
}

int		set_lst(t_ls **lst, t_opt *opt, int ac, char **av)
{
	int		i;
	int		j;
	t_ls	*files;
	t_max	*max;

	i = 0;
	j = set_opt(opt, av);
	if (ac > 1 && (files = init_ls()))
	{
		sort_av(av);
		while (av[++i])
		{
			if ((av[i][0] == '-' && i >= j) || av[i][0] != '-')
				if (!(max = push_lst(lst, &files, opt, av[i])) && opt->l)
					return (-1);
		}
		files->path ? display_file_lst(&files, &max, opt, lst) : free(files);
	}
	if (ac == 1 || (!(*lst)->path && !files->path && !errno))
	{
		(*lst)->path = ft_strdup(".");
		(*lst)->folder = opendir(".");
	}
	return (1);
}
