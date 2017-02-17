/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:43:10 by garouche          #+#    #+#             */
/*   Updated: 2016/11/28 20:29:10 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*buf;
	unsigned char	*buf2;

	if (n == 0)
		return (0);
	buf = (unsigned char*)s1;
	buf2 = (unsigned char*)s2;
	i = 0;
	while (i + 1 < n && buf[i] == buf2[i])
		i++;
	return (buf[i] - buf2[i]);
}
