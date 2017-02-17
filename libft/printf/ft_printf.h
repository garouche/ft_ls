/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 21:57:58 by garouche          #+#    #+#             */
/*   Updated: 2017/02/16 15:42:50 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct		s_settings
{
	int				z_flag;
	int				space_flag;
	int				plus_flag;
	int				minus_flag;
	int				num_flag;
	char			mod;
	char			conv;
	int				precision;
	int				len;
}					t_set;
void				get_len(char *str, t_set **set);
int					display(char **str, char **arg, t_set **set, char **prec);
void				init_set(t_set **set);
int					apply_flags(t_set **set, char **result);
char				*return_arg(va_list ap, t_set **set);
char				*get_arg(char *str, t_set **set);
int					copy_arg(va_list ap, char **str, int nb, t_set **set);
void				str_join(char **dest, char **src1, char *src2);
char				*is_char(va_list ap, t_set **set);
char				*is_str(va_list ap, t_set **set);
char				*valid_arg(char *str, char *arg);
int					get_set(t_set **set, char *str, va_list ap);
char				to_char(char c, t_set **set);
char				*to_base(int base, t_set **set, long long n);
char				*to_utf8(wchar_t alpha, t_set **set);
char				*utf_mask(int nb);
unsigned int		to_octal(unsigned int n);
int					ft_printf(const char *str, ...);
char				*is_signed(va_list ap, t_set **set);
char				*is_unsigned(va_list ap, t_set **set);
int					nb_digit(long long n, int base, t_set **set);
#endif
