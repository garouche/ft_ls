/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 14:50:41 by garouche          #+#    #+#             */
/*   Updated: 2016/11/30 21:13:21 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		while (big[i] && little[j] && big[i] == little[j] && i < len)
		{
			j++;
			i++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i - j]);
		i = i - j;
		j = 0;
		i++;
	}
	if (little[0] == '\0')
		return ((char *)big);
	else
		return (NULL);
}
