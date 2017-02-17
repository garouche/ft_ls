/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:58:18 by garouche          #+#    #+#             */
/*   Updated: 2016/11/29 18:11:45 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str2len(const char *s, char c, int a)
{
	int i;

	i = 0;
	if (s == NULL)
		return (1);
	while (s[a] && s[a] != c)
	{
		i++;
		a++;
	}
	return (i);
}

int		ft_str3len(const char *s, char c)
{
	size_t word;
	size_t i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c)
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word);
}

char	**ft_strsplit(char const *s, char c)
{
	int		a;
	size_t	n;
	char	**str;

	a = 0;
	n = 0;
	if (s == NULL)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * ft_str3len(s, c) + 1);
	if (str == NULL)
		return (NULL);
	while (s[a])
	{
		if (s[a] != c)
		{
			str[n] = ft_strsub(s, a, ft_str2len(s, c, a));
			a = a + ft_str2len(s, c, a);
			n++;
		}
		if (s[a])
			a++;
	}
	str[n] = NULL;
	return (str);
}
