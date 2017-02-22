/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:00:01 by garouche          #+#    #+#             */
/*   Updated: 2017/02/22 18:15:16 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	open_cur_dir(t_dir **dir)
{
	(*dir)->path = opendir(".");
	(*dir)->dir_name = ft_strjoin("", ".");
	(*dir)->next = NULL;
}

int    set_dir(t_dir **dir, int ac, char **av, t_ls **ls)
{
	static int j = 1;
	char *str;

	*dir = malloc(sizeof(t_dir));
	(*dir)->dir_name = NULL;
	(*dir)->path = NULL;
	if (j > ac)
		return (0);
	if (ac > 1)
	{
		while (av[j])
		{
			if (av[j][0] != '-')
			{
				(*dir)->dir_name = av[j];
				(*dir)->next = NULL;
				if (((*dir)->path = opendir(av[j])) || errno == 13)
				{
					j++;
					return (1);
				}
				else if (errno == 20)
					display_file(av[j], ls);
				else
					printf("ls: %s: %s\n", av[j], strerror(errno));
			}
			j++;
		}

	}
	if ((ac == 1 || (*dir)->dir_name == NULL))
		open_cur_dir(dir);
	j++;
	return (1);
}
