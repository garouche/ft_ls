/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:27:17 by garouche          #+#    #+#             */
/*   Updated: 2017/02/18 17:19:00 by garouche         ###   ########.fr       */
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
	char			*bufpath;
	struct stat		*st;
	struct passwd	*pw;
	struct group	*grp;
	struct s_ls 	*next;
}					t_ls;

typedef struct		s_dir
{
	DIR	*path;
	struct dirent *dir;
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

#endif
