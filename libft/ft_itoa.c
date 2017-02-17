/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:53:00 by garouche          #+#    #+#             */
/*   Updated: 2016/11/28 19:35:18 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nblen(int n)
{
	int i;

	i = 0;
	if (n < 0 && n != -2147483648)
		n = -n;
	else if (n == -2147483648)
		n = 2147483647;
	while (n / 10 > 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

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
