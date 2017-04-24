/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:08:23 by garouche          #+#    #+#             */
/*   Updated: 2016/11/25 16:35:04 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*buf;
	const char		*buf2;

	i = 0;
	buf = (unsigned char*)dest;
	buf2 = (const char*)src;
	while (i < n)
	{
		buf[i] = buf2[i];
		if (buf[i] == (unsigned char)c)
			return (&buf[i + 1]);
		i++;
	}
	return (NULL);
}
