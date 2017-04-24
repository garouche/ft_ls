/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:35:00 by garouche          #+#    #+#             */
/*   Updated: 2017/04/24 14:52:46 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <dirent.h>
# include <sys/xattr.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <uuid/uuid.h>
# include <stdio.h>

typedef struct		s_lst
{
	DIR				*folder;
	struct stat		st;
	char			*usr;
	char			*grp;
	char			*path;
	char			*lnk;
	int				uid;
	int				gid;
	int				errn;
	int				attr;
	int				acl;
	struct s_lst	*next;
}					t_ls;

typedef struct		s_max
{
	size_t			block;
	size_t			lnk;
	size_t			usrname;
	size_t			grpname;
	size_t			size;
	size_t			major;
	size_t			minor;
	size_t			device;
}					t_max;
typedef struct		s_options
{
	char			l;
	char			r;
	char			rr;
	char			a;
	char			t;
	char			gg;
	char			o;
}					t_opt;
void				bad_options(char **av, int i, int j);
void				l_node(t_ls **buf, char path[1025]);
void				manage_dir(t_ls **lst, t_ls **new_dir, t_opt *opt,
	t_max *max);
void				cat_and_free(char **s1, char *s2);
char				*str_time(t_ls **lst);
char				*str_usr(t_ls **lst, t_max *max);
char				*str_grp(t_ls **lst, t_max *max);
char				*str_size(t_ls **lst, t_max *max);
void				get_max(t_ls *buf, t_max *max);
int					l_flag(t_ls **lst, t_max *max);
t_max				*push_lst(t_ls **ptr, t_ls **files, t_opt *opt, char *av);
void				sort_ls(t_ls *buf, t_ls **lst, t_opt *opt);
t_ls				*manage_files_lst(t_opt *opt, char *path, char *name);
void				display_file_name(t_ls **lst, char *name, t_opt *opt);
int					manage_path(char path[1025], t_ls **lst, struct dirent *d);
int					display_file_lst(t_ls **lst, t_max **max, t_opt *opt,
t_ls **dir);
void				free_lst(t_ls **lst);
int					scroll_lst(t_ls **lst, t_opt *opt);
int					set_opt(t_opt *opt, char **av);
int					set_lst(t_ls **lst, t_opt *opt, int ac, char **av);
t_ls				*init_ls(void);
int					cat_ls(t_ls **lst1, t_ls **lst2);
void				sort_av(char **av);
void				display_name(char *path, int error, int fd);
#endif
