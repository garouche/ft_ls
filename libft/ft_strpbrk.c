/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 17:19:03 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 15:33:57 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;
	char	*res;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s2[i])
	{
		if ((res = ft_strchr(s1, s2[i])) != NULL)
			return (res);
		i++;
	}
	return (NULL);
}
