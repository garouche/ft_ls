/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:06:57 by garouche          #+#    #+#             */
/*   Updated: 2016/11/29 18:14:54 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t r;

	j = ft_strlen(dst);
	i = 0;
	r = ft_strlen(dst);
	while (src[i] && j < size - 1)
		dst[j++] = src[i++];
	dst[j] = '\0';
	if (j >= size)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + j - i);
}
