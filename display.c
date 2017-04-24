/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 21:52:19 by garouche          #+#    #+#             */
/*   Updated: 2017/04/24 14:56:34 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_file_lst(t_ls **lst, t_max **max, t_opt *opt, t_ls **dir)
{
	t_ls	*ptr;
	int		i;

	i = 0;
	ptr = *lst;
	while (ptr)
	{
		if (ptr->path)
		{
			if (opt->l)
				l_flag(&ptr, *max);
			display_file_name(&ptr, ptr->path, opt);
			if (opt->l)
				write(1, "\n", 1);
			i++;
		}
		free_lst(&ptr);
		if (ptr && !opt->l)
			ft_putchar('\t');
	}
	if ((i && !opt->l) || ((*dir)->next && opt->l))
		ft_putchar('\n');
	if (opt->l)
		free(*max);
	return (1);
}

void	display_file_name(t_ls **lst, char *name, t_opt *opt)
{
	char	*color;
	char	buf[2048];

	color = NULL;
	if (opt->gg && S_ISREG((*lst)->st.st_mode)
	&& ((*lst)->st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		color = "\x1b[31m";
	else if (opt->gg && S_ISDIR((*lst)->st.st_mode))
		color = "\x1b[36;1m";
	else if (opt->gg && S_ISLNK((*lst)->st.st_mode))
		color = "\x1b[35m";
	else if (opt->gg && S_ISCHR((*lst)->st.st_mode))
		color = "\x1b[34;43m";
	else if (opt->gg && S_ISBLK((*lst)->st.st_mode))
		color = "\x1b[34;46m";
	color ? ft_putstr(color) : 0;
	ft_putstr(name);
	color ? ft_putstr("\x1b[0m") : 0;
	if (S_ISLNK((*lst)->st.st_mode) && opt->l)
	{
		buf[0] = 0;
		ft_strcat(buf, " -> ");
		ft_strcat(buf, (*lst)->lnk);
		ft_putstr(buf);
	}
}

void	display_dir_lst(t_ls **lst, t_opt *opt, char path[1025])
{
	t_ls			*files;
	t_ls			*new_dir;
	t_ls			*buf;
	struct dirent	*d;
	t_max			*max;

	opt->l ? max = ft_memalloc(sizeof(t_max)) : 0;
	new_dir = init_ls();
	(!(files = init_ls()) || !new_dir) ? exit(EXIT_FAILURE) : 0;
	while ((d = readdir((*lst)->folder)))
	{
		if (*d->d_name != '.' || opt->a >= 1)
		{
			manage_path(path, lst, d);
			if (!(buf = manage_files_lst(opt, (char*)path, d->d_name)))
				exit(EXIT_FAILURE);
			opt->l ? get_max(buf, max) : 0;
			sort_ls(buf, &files, opt);
			if (opt->rr && S_ISDIR(buf->st.st_mode) &&
	ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, "..") && buf->st.st_size)
				push_lst(&new_dir, NULL, opt, path);
		}
	}
	manage_dir(lst, &new_dir, opt, max);
	display_file_lst(&files, &max, opt, lst);
}

int		display(t_ls **lst, t_opt *opt)
{
	char	path[1025];
	char	*str;

	if ((*lst)->folder == NULL)
	{
		if ((*lst)->errn == 13 && (*lst)->next)
		{
			str = ft_memalloc(ft_strlen((*lst)->path) + 3);
			ft_strcat(str, (*lst)->path);
			ft_strcat(str, ":\n");
			ft_putstr(str);
			free(str);
		}
		display_name((*lst)->path, (*lst)->errn, 2);
		if ((*lst)->next)
			ft_putchar('\n');
	}
	else
	{
		display_dir_lst(lst, opt, path);
		(*lst)->next && !opt->l ? write(1, "\n", 1) : 0;
	}
	return (0);
}

int		scroll_lst(t_ls **lst, t_opt *opt)
{
	t_ls	*ptr;
	int		i;
	char	*str;

	i = 0;
	ptr = *lst;
	while (ptr)
	{
		if ((ptr->folder && i) || (!i && ptr->next))
		{
			str = ft_memalloc(ft_strlen(ptr->path) + 3);
			ft_strcat(str, ptr->path);
			ft_strcat(str, ":\n");
			ft_putstr(str);
			free(str);
		}
		display(&ptr, opt);
		free_lst(&ptr);
		i++;
	}
	return (0);
}
