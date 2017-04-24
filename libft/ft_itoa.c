/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:53:00 by garouche          #+#    #+#             */
/*   Updated: 2017/04/04 13:55:39 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_nbr(char *res, int i, int n)
{
	res[i] = '\0';
	while (n % 10 != n)
	{
		res[i - 1] = -(n % 10) + '0';
		n = n / 10;
		i--;
	}
	res[i - 1] = -n + '0';
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	size_t	i;

	i = ft_nblen(n);
	if (n >= 0)
	{
		res = ft_memalloc(i + 1);
		if (res == NULL)
			return (NULL);
		n = -n;
	}
	else
	{
		i = i + 1;
		res = ft_memalloc(i + 1);
		if (res == NULL)
			return (NULL);
		res[0] = '-';
	}
	res = ft_nbr(res, i, n);
	return (res);
}
