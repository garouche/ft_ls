/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:43:43 by garouche          #+#    #+#             */
/*   Updated: 2016/11/25 16:34:22 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *buf;
	unsigned char *buf2;
	unsigned long i;

	i = 0;
	buf = (unsigned char*)dest;
	buf2 = (unsigned char*)src;
	while (i < n)
	{
		buf[i] = buf2[i];
		i++;
	}
	return (buf);
}
