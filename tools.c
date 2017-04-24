/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:51:07 by garouche          #+#    #+#             */
/*   Updated: 2017/04/24 14:48:05 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_lst(t_ls **lst)
{
	t_ls *ptr;

	ptr = *lst;
	*lst = (*lst)->next;
	ptr->path ? free(ptr->path) : 0;
	ptr->usr ? free(ptr->usr) : 0;
	ptr->grp ? free(ptr->grp) : 0;
	ptr->lnk ? free(ptr->lnk) : 0;
	free(ptr);
}

void	display_name(char *path, int error, int fd)
{
	char	*str;
	char	*ptr;

	str = ft_strrchr(path, '/');
	str = (str ? str + 1 : path);
	if (!(ptr = ft_memalloc(ft_strlen(str) + ft_strlen(strerror(error)) + 8)))
		exit(EXIT_FAILURE);
	ft_strcat(ptr, "ls: ");
	ft_strcat(ptr, str);
	ft_strcat(ptr, ": ");
	ft_strcat(ptr, strerror(error));
	ft_strcat(ptr, "\n");
	ft_putstr_fd(ptr, fd);
	free(ptr);
}

int		set_opt(t_opt *opt, char **av)
{
	int i;
	int j;

	j = 1;
	i = 0;
	ft_memset(opt, 0, sizeof(opt));
	while (av[j] && av[j][0] == '-')
	{
		while (av[j][i])
		{
			bad_options(av, i, j);
			opt->l += (av[j][i] == 'l' ? 1 : 0);
			opt->gg += (av[j][i] == 'G' ? 1 : 0);
			opt->r += (av[j][i] == 'r' ? 1 : 0);
			opt->rr += (av[j][i] == 'R' ? 1 : 0);
			opt->a += (av[j][i] == 'a' ? 1 : 0);
			opt->t += (av[j][i] == 't' ? 1 : 0);
			opt->o += (av[j][i] == '-' ? 1 : 0);
			i++;
		}
		i = 0;
		j++;
	}
	return (ft_memcheck(opt, sizeof(t_opt)) ? j : j - 1);
}

int		cat_ls(t_ls **lst1, t_ls **lst2)
{
	t_ls *ptr;

	if ((*lst1)->path && (*lst2)->path == NULL)
	{
		free(*lst2);
		*lst2 = *lst1;
	}
	else if ((*lst1)->next == NULL && (*lst1)->path)
	{
		(*lst1)->next = *lst2;
		*lst2 = *lst1;
	}
	else if ((*lst1)->path)
	{
		ptr = *lst1;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = *lst2;
		*lst2 = *lst1;
	}
	return (1);
}

void	sort_av(char **av)
{
	char	*buf;
	int		i;

	i = 1;
	while (av[i] && av[i][0] == '-')
		i++;
	while (av[i] && av[i + 1])
	{
		if (ft_strcmp(av[i + 1], av[i]) < 0)
		{
			buf = av[i];
			av[i] = av[i + 1];
			av[i + 1] = buf;
			i = 1;
		}
		i++;
	}
}
