/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:32:51 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 16:28:15 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*is_signed(va_list ap, t_set **set)
{
	long long	l;
	char		*flag;

	l = 0;
	flag = ft_strchr("hHlLjz", (**set).mod);
	l = (flag[0] == 0 ? va_arg(ap, int) : l);
	l = ((**set).mod == 'H' ? (char)va_arg(ap, int) : l);
	l = ((**set).mod == 'h' ? (short)va_arg(ap, int) : l);
	l = ((**set).mod == 'L' ? va_arg(ap, long long) : l);
	l = ((**set).mod == 'l' ? va_arg(ap, long) : l);
	l = ((**set).mod == 'j' ? va_arg(ap, intmax_t) : l);
	l = ((**set).mod == 'z' ? va_arg(ap, long) : l);
	return (to_base(10, set, l));
}

char	*is_unsigned(va_list ap, t_set **set)
{
	unsigned long long	l;
	char				*flag;

	l = 0;
	flag = ft_strchr("hHlLjz", (**set).mod);
	l = (flag[0] == 0 ? va_arg(ap, unsigned int) : l);
	l = ((**set).mod == 'H' ? (unsigned char)va_arg(ap, int) : l);
	l = ((**set).mod == 'h' ? (unsigned short)va_arg(ap, int) : l);
	l = ((**set).mod == 'L' ? va_arg(ap, unsigned long long) : l);
	l = ((**set).mod == 'l' ? va_arg(ap, unsigned long) : l);
	l = ((**set).mod == 'j' ? va_arg(ap, uintmax_t) : l);
	l = ((**set).mod == 'z' ? va_arg(ap, size_t) : l);
	if ((**set).conv == 'o')
		return (to_base(8, set, l));
	else if ((**set).conv == 'x' || (**set).conv == 'X' || (*set)->conv == 'p')
		return (to_base(16, set, l));
	else
		return (to_base(10, set, l));
}

int		copy_str(wchar_t buf, char **str, t_set **set)
{
	char	*ptr;
	int		len;

	ptr = to_utf8(buf, set);
	len = (int)ft_strlen(*str) + (int)ft_strlen(ptr);
	if ((*set)->precision >= 0 && len > (*set)->precision)
	{
		free(ptr);
		return (0);
	}
	else
	{
		str_join(str, str, ptr);
		free(ptr);
		if (buf > 255 && MB_CUR_MAX == 1)
		{
			free(*str);
			return (-1);
		}
	}
	return (1);
}

char	*is_str(va_list ap, t_set **set)
{
	wchar_t	*buf;
	char	*str;

	str = NULL;
	if ((**set).conv == 's' && (**set).mod != 'l')
		str = ft_strjoin("", va_arg(ap, char*));
	else if ((buf = va_arg(ap, wchar_t*)) != NULL)
	{
		if ((str = ft_memalloc(2)) == NULL)
			return (NULL);
		while (*buf)
		{
			if (copy_str(*buf, &str, set) == -1)
				return (NULL);
			buf += 1;
		}
	}
	return ((str == NULL ? ft_strjoin("", "(null)") : str));
}

char	*is_char(va_list ap, t_set **set)
{
	wint_t	wc;
	char	*c;

	if ((wc = (va_arg(ap, wint_t))) > 255 && MB_CUR_MAX == 1)
		return (NULL);
	else if (((**set).conv == 'c' && (**set).mod != 'l') || (*set)->conv == '%'
			|| (wc < 255 && MB_CUR_MAX == 1))
	{
		if ((c = ft_memalloc(2)) == NULL)
			return (NULL);
		*c = wc;
		return (c);
	}
	else
		return (to_utf8(wc, set));
}
