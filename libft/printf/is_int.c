/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:46:22 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 15:39:10 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		nb_digit(long long n, int base, t_set **set)
{
	int					i;
	unsigned long long	ull;

	ull = n;
	i = 0;
	if (n == 0 && ull == 0)
		return (1);
	if (ft_strchr("dDi", (**set).conv) != NULL)
	{
		while (n != 0)
		{
			n = n / base;
			i++;
		}
	}
	else
	{
		while (ull != 0)
		{
			ull = ull / base;
			i++;
		}
	}
	return (i);
}

char	*to_str(char **str, t_set **set, int base, long long n)
{
	unsigned long long	ull;
	size_t				i;

	i = ft_strlen(*str) - 1;
	ull = n;
	if (ft_strchr("dDi", (**set).conv) != NULL)
	{
		while (n != 0)
		{
			str[0][i--] = to_char(n % base, set);
			n = n / base;
		}
	}
	else
	{
		while (ull != 0)
		{
			str[0][i--] = to_char(ull % base, set);
			ull = ull / base;
		}
	}
	return (*str);
}

char	*to_base(int base, t_set **set, long long n)
{
	int		j;
	char	*str;

	j = nb_digit(n, base, set);
	if ((str = malloc(j + 2)) == NULL)
		return (NULL);
	ft_memset(str, '0', j + 2);
	if (ft_strchr("dDi", (**set).conv) != NULL && n < 0)
	{
		str[0] = '-';
		j += 1;
	}
	str[j] = '\0';
	str = to_str(&str, set, base, n);
	return (str);
}

char	to_char(char c, t_set **set)
{
	if (c < 0)
		c = -c;
	if (c > 9 && ((**set).conv == 'x' || (*set)->conv == 'p'))
		c = 'a' + (c - 10);
	else if (c > 9 && (**set).conv == 'X')
		c = 'A' + (c - 10);
	else
		c += '0';
	return (c);
}

void	init_set(t_set **set)
{
	(*set)->z_flag = 0;
	(*set)->space_flag = 0;
	(*set)->plus_flag = 0;
	(*set)->minus_flag = 0;
	(*set)->num_flag = 0;
	(*set)->mod = 0;
	(*set)->conv = 0;
	(*set)->precision = -1;
	(*set)->len = -1;
}
