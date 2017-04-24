/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:52:08 by garouche          #+#    #+#             */
/*   Updated: 2016/11/26 20:16:04 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*z;

	z = (void*)malloc(sizeof(void) * size);
	if (z == NULL)
		return (NULL);
	ft_memset(z, 0, size);
	return (z);
}
