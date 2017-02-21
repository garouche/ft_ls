/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:27:17 by garouche          #+#    #+#             */
/*   Updated: 2017/02/21 18:27:50 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

typedef struct		s_ls
{
	struct dirent	*dir;
	char			*bufpath;
	struct stat		*st;
	struct passwd	*pw;
	struct group	*grp;
	struct s_ls 	*next;
}					t_ls;

typedef struct		s_dir
{
	DIR	*path;
	struct s_dir *next;
	char		*dir_name;
	char		*start;
}					t_dir;

typedef struct		s_options
{
	char	l;
	char	r;
	char	R;
	char	a;
	char	t;
}					t_opt;
void	cat_list(t_dir **dir, t_dir **buf);
void	set_opt(t_opt **opt, int ac, char **av);
void	set_path(t_dir **dir, t_dir **ptr, t_ls **ls);
void	set_dir(t_dir **dir, int ac, char **av);
t_dir	*push_back_dir(t_dir **dir, t_dir **buf, t_ls **ls);
t_dir	*push_front_dir(t_dir **dir, t_dir **buf, t_ls **ls);
int		sort_type(char *str, t_opt **opt, t_ls **ls);

#endif
