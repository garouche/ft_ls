/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:16:48 by garouche          #+#    #+#             */
/*   Updated: 2016/11/29 18:17:28 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		st;
	int		nd;
	char	*str;

	i = 0;
	st = 0;
	if (s == NULL)
		return (NULL);
	nd = ft_strlen(s);
	while (s[st] && (s[st] == ' ' || s[st] == '\t' || s[st] == '\n'))
		st++;
	while (s[nd - 1] == ' ' || s[nd - 1] == '\t' || s[nd - 1] == '\n')
		nd--;
	if (nd - st > 0)
	{
		str = ft_strsub(s, st, nd - st);
		if (str == NULL)
			return (NULL);
	}
	else
		return (ft_strdup(""));
	return (str);
}
