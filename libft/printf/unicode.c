/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 20:23:08 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 15:32:01 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_utf8(wchar_t alpha, t_set **set)
{
	char	*mask;
	char	*result;
	int		nb;

	if (alpha >= 55296)
		return (NULL);
	nb = nb_digit(alpha, 2, set);
	mask = utf_mask(nb);
	nb = (ft_strlen((char*)mask));
	nb = (nb > 0 ? nb : 1);
	if ((result = ft_memalloc(5)) == NULL)
		return (NULL);
	if (nb > 1)
	{
		while (--nb >= 0)
		{
			result[nb] = ((alpha & 0b111111) | mask[nb]);
			alpha = alpha >> 6;
		}
	}
	else
		result[0] = alpha;
	return (result);
}

char	*utf_mask(int nb)
{
	static char str[4][5] = {
		{0b00000000, '\0'},
		{0b11000000, 0b10000000, '\0'},
		{0b11100000, 0b10000000, 0b10000000, '\0'},
		{0b11110000, 0b10000000, 0b10000000, 0b10000000, '\0'}
	};

	if (nb <= 7)
		return (str[0]);
	if (nb <= 11)
		return (str[1]);
	else if (nb <= 16)
		return (str[2]);
	else if (nb <= 21)
		return (str[3]);
	else
		return (str[0]);
}
