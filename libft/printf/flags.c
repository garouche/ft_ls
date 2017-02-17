/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:39:49 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 16:13:34 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_precision(t_set **set, char **arg, char **prec)
{
	int		i;
	char	*buf;

	i = (*set)->precision - ft_strlen(*arg);
	if ((*set)->precision == 0 && ft_atoi(*arg) == 0 &&
			ft_strchr("spdiouxX", (*set)->conv) != NULL)
		ft_bzero(*arg, ft_strlen(*arg));
	else if ((*set)->conv == 's' && (int)ft_strlen(*arg) > (*set)->precision)
		arg[0][(*set)->precision] = '\0';
	else if (i > 0 && (*set)->conv != 's')
	{
		if ((buf = ft_memalloc(i + 1)) == NULL)
			return ;
		ft_memset(buf, '0', i);
		str_join(prec, prec, buf);
		free(buf);
	}
}

void	space_and_plus(t_set **set, char **str)
{
	char *sign;

	if (**str != '-' && ((*set)->space_flag == 1 || (*set)->plus_flag == 1))
	{
		if ((sign = ft_memalloc(2)) == NULL)
			return ;
		sign[0] = ((*set)->plus_flag == 1 ? '+' : ' ');
		str_join(str, &sign, *str);
		free(sign);
	}
}

void	num_flag(t_set **set, char **prec, char **arg)
{
	char *ptr;

	ptr = NULL;
	if (((*set)->conv == 'x' && ft_atoi(*arg) > 0) || (*set)->conv == 'p')
		ptr = "0x";
	else if ((*set)->conv == 'X' && ft_atoi(*arg) > 0)
		ptr = "0X";
	if (((*set)->conv == 'o' && (*set)->precision == 0) || ((*set)->conv == 'o'
		&& ft_atoi(*arg) > 0 && (*set)->precision == -1))
		ptr = "0";
	if (ptr != NULL)
		str_join(prec, &ptr, *prec);
}

void	apply_len(t_set **set, char **str, char **arg, char **prec)
{
	char	*len;
	int		i;
	int		j;

	j = ((*set)->conv == 'c' && **arg == 0 ? 1 : ft_strlen(*arg));
	i = (*set)->len - j - ft_strlen(*str) - ft_strlen(*prec);
	if (((*set)->precision > 0 && (!ft_strchr("cs", (*set)->conv))) ||
			(*set)->minus_flag == 1)
		(*set)->z_flag = 0;
	if (i > 0)
	{
		if ((len = ft_memalloc(i + 1)) == NULL)
			return ;
		if ((*set)->z_flag == 1 && (*set)->minus_flag == 0)
			ft_memset(len, '0', i);
		else
			ft_memset(len, ' ', i);
		if ((*set)->z_flag == 0)
			str_join(str, &len, *str);
		else
			str_join(prec, prec, len);
		free(len);
	}
}

int		apply_flags(t_set **set, char **arg)
{
	char	*str;
	char	*prec;

	str = ft_memalloc(2);
	prec = ft_memalloc(2);
	if (prec == NULL || str == NULL)
		return (-1);
	if (ft_strchr("cs", (*set)->conv) == NULL && **arg == '-' &&
			ft_atoi(*arg) != 0)
	{
		prec[0] = '-';
		ft_memmove(*arg, *arg + 1, ft_strlen(*arg));
	}
	if ((*set)->precision >= 0 && (*set)->conv != '%' && (*set)->conv != 'c')
		apply_precision(set, arg, &prec);
	if ((*set)->conv == 'i' || (*set)->conv == 'd')
		space_and_plus(set, &prec);
	if ((*set)->num_flag == 1)
		num_flag(set, &prec, arg);
	if ((*set)->len > 0)
		apply_len(set, &str, arg, &prec);
	return (display(&str, arg, set, &prec));
}
