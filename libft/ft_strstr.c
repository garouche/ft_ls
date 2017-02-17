/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:00:26 by garouche          #+#    #+#             */
/*   Updated: 2016/11/29 18:16:17 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (big[i] && little[j] && j < ft_strlen(little))
	{
		while (little[j] == big[i] && big[i] && little[j])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(little))
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
