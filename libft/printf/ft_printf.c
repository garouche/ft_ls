/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 15:56:17 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 16:13:05 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_set	*set;
	int		r;
	char	*buf;

	if ((set = malloc(sizeof(t_set))) == NULL)
		return (-1);
	if ((buf = ft_memalloc(ft_strlen(str) + 2)) == NULL)
		return (-1);
	va_start(ap, str);
	ft_memcpy(buf, str, ft_strlen(str));
	r = get_set(&set, buf, ap);
	va_end(ap);
	free(set);
	free(buf);
	if (r == -1)
		return (-1);
	else
		return (r);
}
