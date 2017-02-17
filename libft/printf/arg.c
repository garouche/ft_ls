/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 17:39:19 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 16:24:54 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		copy_arg(va_list ap, char **str, int nb, t_set **set)
{
	char	*arg;
	char	*ptr;
	int		i;

	i = nb;
	if ((ptr = get_arg(&str[0][nb], set)) != NULL)
	{
		if ((arg = return_arg(ap, set)) == NULL)
			return (-1);
	}
	else
	{
		if ((arg = ft_memalloc(2)) == NULL)
			return (-1);
		init_set(set);
		while ((ft_strchr(" 0123456789#-+hjlz.%", str[0][++i])) && str[0][i])
			;
		(*set)->conv = ((*set)->conv == 0 ? str[0][i] : (*set)->conv);
		arg = ft_memset(arg, str[0][i], 1);
		get_len(*str + nb, set);
		ptr = &str[0][i + 1];
	}
	i = write(1, *str, nb);
	*str = ptr;
	return (i + apply_flags(set, &arg));
}

void	str_join(char **dest, char **src1, char *src2)
{
	char *ptr;

	ptr = *dest;
	*dest = ft_strjoin(*src1, src2);
	free(ptr);
}

int		display(char **str, char **arg, t_set **set, char **prec)
{
	int i;
	int j;
	int k;

	k = ft_strlen(*prec);
	i = ft_strlen(*arg);
	if (i == 0 && (*set)->conv == 'c')
		i = 1;
	j = ft_strlen(*str);
	if ((*set)->minus_flag == 0)
		write(1, *str, j);
	write(1, *prec, k);
	write(1, *arg, i);
	if ((*set)->minus_flag == 1)
		write(1, *str, j);
	free(*str);
	free(*arg);
	free(*prec);
	return (i + j + k);
}
