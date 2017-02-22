/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:58:38 by garouche          #+#    #+#             */
/*   Updated: 2017/02/22 15:34:20 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
int		sort_type(t_dir **ptr, t_opt **opt, t_ls **ls)
{
	int i;
	char *str;
	t_ls *buf;
	
	if	((*opt)->t == 1)
	{
		buf = malloc(sizeof(t_ls));
		buf->st = malloc(sizeof(struct stat));
		lstat((*ptr)->dir_name, buf->st);
		i = buf->st->st_mtime - (*ls)->st->st_mtime;
		free(buf);
		free(buf->st);
	}
	else
	{
		if ((str = ft_strchr((*ptr)->dir_name, '/') + 1) == NULL)
			str = (*ptr)->dir_name + 2;
		i = ft_strcmp((*ls)->dir->d_name, str);
	}
	if ((*opt)->r == 1)
		return (-i);
	else
		return (i);
}

int		set_path(t_dir **dir, t_dir **ptr, t_ls **ls)
{
	char *str;

	str = (ft_strcmp((*dir)->start, (*dir)->dir_name) == 0 ? "" : "/");
	str = ft_strjoin((*dir)->dir_name, str);
	(*ptr)->dir_name = ft_strjoin(str, (*ls)->dir->d_name);
	free(str);
	(*ptr)->start = (*dir)->start;
	if (((*ptr)->path = opendir((*ptr)->dir_name)) == NULL)
		(*ptr)->error = ft_strjoin("", strerror(errno));
	return(1);
}

void	set_opt(t_opt **opt, int ac, char **av)
{
	int i;
	int j;

	j = 1;
	i = 0;
	*opt = malloc(sizeof(t_opt));
	(*opt)->l = 0;
	(*opt)->r = 0;
	(*opt)->R = 0;
	(*opt)->a = 0;
	(*opt)->t = 0;
	while (av[j] && av[j][0] == '-')
	{
		while (av[j][i])
		{
			(*opt)->l += (av[j][i] == 'l' ? 1 : 0);
			(*opt)->r += (av[j][i] == 'r' ? 1 : 0);
			(*opt)->R += (av[j][i] == 'R' ? 1 : 0);
			(*opt)->a += (av[j][i] == 'a' ? 1 : 0);
			(*opt)->t += (av[j][i] == 't' ? 1 : 0);
			i++;
		}
		i = 0;
		j++;
	}
}

void    cat_list(t_dir **dir, t_dir **buf)
{
	t_dir   *ptr;
	t_dir   *ptr2;


	if ((*dir)->next == NULL && *buf)
		(*dir)->next = *buf;
	else if (*buf)
	{
		ptr2 = *buf;
		while (ptr2->next)
			ptr2 = ptr2->next;
		ptr2->next = (*dir)->next;
		(*dir)->next = *buf;
	}
}
