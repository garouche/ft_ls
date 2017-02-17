/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 06:52:28 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 15:39:53 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>

char	*valid_arg(char *str, char *arg)
{
	int		i;
	char	*buf;

	buf = " 0123456789#-+hjlz.%";
	i = 0;
	while (str[++i] != arg[0] && ((ft_strchr(buf, str[i])) != NULL))
	{
		if (ft_isdigit(str[i]) && str[i] != '0')
			buf = "0123456789hjzl.";
		if (str[i] == '.')
			buf = "0123456789hjzl";
		if (ft_strchr("hjl", str[i]) != NULL)
		{
			if ((ft_strcmp(buf, "hl") == 0) || str[i] == 'j' || str[i] == 'z')
				buf = "";
			else
				buf = "hl";
		}
	}
	if (str[i] == arg[0])
		return (&str[i] + 1);
	else
		return (NULL);
}

void	get_len(char *str, t_set **set)
{
	int i;

	i = 0;
	while (str[++i] && str[i] != (*set)->conv)
	{
		if (ft_isdigit(str[i]) && str[i] != '0' && str[i - 1] != '.' &&
				(*set)->len == -1)
			(**set).len = ft_atoi(&str[i]);
		if (str[i] == '0' && str[i - 1] != '.' && (!ft_isdigit(str[i - 1])))
			(**set).z_flag = 1;
		if (str[i] == '.')
			(*set)->precision = ft_atoi(&str[i + 1]);
		(*set)->num_flag = (str[i] == '#' ? 1 : (*set)->num_flag);
		(*set)->minus_flag = (str[i] == '-' ? 1 : (*set)->minus_flag);
		(**set).plus_flag = (str[i] == '+' ? 1 : (*set)->plus_flag);
		(**set).space_flag = (str[i] == ' ' ? 1 : (*set)->space_flag);
		(**set).mod = (str[i] == 'j' ? 'j' : (**set).mod);
		(**set).mod = (str[i] == 'h' ? 'h' : (**set).mod);
		(**set).mod = (str[i] == 'l' ? 'l' : (**set).mod);
		(**set).mod = (str[i] == 'z' ? 'z' : (**set).mod);
		(**set).mod = (str[i] == 'h' && str[i - 1] == 'h' ? 'H' : (**set).mod);
		(**set).mod = (str[i] == 'l' && str[i - 1] == 'l' ? 'L' : (**set).mod);
	}
}

char	*get_arg(char *str, t_set **set)
{
	int		i;
	char	*arg;

	i = 0;
	arg = NULL;
	init_set(set);
	while (str[++i])
	{
		if ((arg = ft_strchr("sSpdDioOuUxXcC%", str[i])) != NULL)
		{
			(**set).conv = arg[0];
			if ((arg = valid_arg(str, arg)) == NULL)
				return (NULL);
			else
			{
				get_len(str, set);
				return (arg);
			}
		}
	}
	return (NULL);
}

char	*return_arg(va_list ap, t_set **set)
{
	char *result;

	result = NULL;
	if (ft_strchr("DOUSC", (*set)->conv) != NULL)
	{
		(*set)->mod = 'l';
		(*set)->conv = ft_tolower((*set)->conv);
	}
	if ((*set)->conv == 'p')
	{
		(*set)->num_flag = 1;
		(*set)->mod = 'l';
	}
	result = ((*set)->conv == 'p' ? is_unsigned(ap, set) : result);
	result = ((*set)->conv == 'x' ? is_unsigned(ap, set) : result);
	result = ((*set)->conv == 'X' ? is_unsigned(ap, set) : result);
	result = ((*set)->conv == 'd' ? is_signed(ap, set) : result);
	result = ((*set)->conv == 'i' ? is_signed(ap, set) : result);
	result = ((*set)->conv == 'u' ? is_unsigned(ap, set) : result);
	result = ((*set)->conv == 'o' ? is_unsigned(ap, set) : result);
	result = ((*set)->conv == 'c' ? is_char(ap, set) : result);
	result = ((*set)->conv == 's' ? is_str(ap, set) : result);
	result = ((*set)->conv == '%' ? ft_strjoin("", "%") : result);
	return (result);
}

int		get_set(t_set **set, char *str, va_list ap)
{
	int		i;
	int		j;
	int		r;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(&str[i], '%') == NULL)
		{
			ft_putstr(&str[i]);
			j += ft_strlen(&str[i]);
			break ;
		}
		if (str[i] == '%')
		{
			if ((r = copy_arg(ap, &str, i, set)) == -1 &&
				(*set)->precision != 0)
				return (-1);
			j += r;
			i = -1;
		}
		i++;
	}
	return (j);
}
