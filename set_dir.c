/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:00:01 by garouche          #+#    #+#             */
/*   Updated: 2017/02/25 22:42:38 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*open_cur_dir(void)
{
	t_dir *dir;

	dir = new_dir();
	dir->path = opendir(".");
	dir->dir_name = ft_strjoin("", ".");
	dir->next = NULL;
	return (dir);
}

void	set_arg(char *av, t_opt **opt, t_ls **ls, t_dir **dir)
{
	t_dir *buf;
	t_dir *buf2;
	t_dir *error;

	buf = new_dir();
	buf->dir_name = av;
	if (*(*dir)->dir_name == 0)
	{
		free(*dir);
		*dir = buf;
		if (((*dir)->path = opendir(av)) == NULL && errno != 13)
		{
			error = *dir;
			*dir = NULL;
		}
	}
	else if (((buf->path = opendir(av)) || errno == 13))
		push_arg(&buf, opt, ls, dir);
	else
		push_arg(&buf, opt, ls, &error);
}

t_dir	*set_dir(int ac, char **av, t_opt **opt, t_ls **ls)
{
	int j;
	t_dir *buf;
	t_dir *buf2;

	j = 0;
	buf2 = new_dir();
	if (ac == 1)
		buf = open_cur_dir();
	if (ac > 1)
	{
		while (av[++j])
		{
			if (av[j][0] != '-')
				set_arg(av[j], opt, ls, &buf2);
		}
	}
	if (ac == 1 || buf2->dir_name == NULL)
		buf2 = open_cur_dir();
	return (buf2);
}
