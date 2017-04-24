/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:38:49 by garouche          #+#    #+#             */
/*   Updated: 2017/04/21 21:06:24 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_ls(int ac, char **av)
{
	t_ls	*lst;
	t_opt	opt;

	if ((lst = init_ls()) == NULL)
		return (-1);
	if (set_lst(&lst, &opt, ac, av) == -1)
		return (-1);
	if (lst->path)
		scroll_lst(&lst, &opt);
	return (1);
}

int	main(int ac, char **av)
{
	ft_ls(ac, av);
	return (0);
}
