/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:58:38 by garouche          #+#    #+#             */
/*   Updated: 2017/02/21 18:31:21 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
int		sort_type(char *str, t_opt **opt, t_ls **ls)
{
	int i;

	if ((*opt)->t == 1)
	{
		printf("%ld TIME\n", (*ls)->st->st_mtime);
	}
	return (i);
}

void	set_path(t_dir **dir, t_dir **ptr, t_ls **ls)
{
	char *str;

	str = (ft_strcmp((*dir)->start, (*dir)->dir_name) == 0 ? "" : "/");
	str = ft_strjoin((*dir)->dir_name, str);
	(*ptr)->dir_name = ft_strjoin(str, (*ls)->dir->d_name);
	free(str);
	(*ptr)->path = opendir((*ptr)->dir_name);
	(*ptr)->start = (*dir)->start;
}

void	set_opt(t_opt **opt, int ac, char **av)
{
	int i;

	i = 0;
	*opt = malloc(sizeof(t_opt));
	(*opt)->l = 0;
	(*opt)->r = 0;
	(*opt)->R = 0;
	(*opt)->a = 0;
	(*opt)->t = 0;
	if (ac > 1 && av[1][0] == '-')
	{
		while (av[1][i])
		{
			(*opt)->l += (av[1][i] == 'l' ? 1 : 0);
			(*opt)->r += (av[1][i] == 'r' ? 1 : 0);
			(*opt)->R += (av[1][i] == 'R' ? 1 : 0);
			(*opt)->a += (av[1][i] == 'a' ? 1 : 0);
			(*opt)->t += (av[1][i] == 't' ? 1 : 0);
			i++;
		}
	}
}

void    set_dir(t_dir **dir, int ac, char **av)
{
	    *dir = malloc(sizeof(t_dir));

		    (*dir)->path = opendir(".");
			    (*dir)->dir_name = "./";
				    (*dir)->next = NULL;

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
