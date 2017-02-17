/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:13:50 by garouche          #+#    #+#             */
/*   Updated: 2016/11/27 15:26:15 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = ft_memalloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	else
		while (s[i])
		{
			str[i] = f(s[i]);
			i++;
		}
	str[i] = '\0';
	return (str);
}
