/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 20:31:00 by garouche          #+#    #+#             */
/*   Updated: 2017/04/24 14:52:13 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	l_node(t_ls **buf, char path[1025])
{
	struct passwd	*usr;
	struct group	*grp;
	acl_t			acl;

	if (S_ISLNK((*buf)->st.st_mode))
	{
		if (!((*buf)->lnk = ft_memalloc(sizeof(char) * 1024)))
			exit(EXIT_FAILURE);
		readlink(path, (*buf)->lnk, 1024);
	}
	if ((usr = getpwuid((*buf)->st.st_uid)))
		(*buf)->usr = ft_strdup(usr->pw_name);
	if ((grp = getgrgid((*buf)->st.st_gid)))
		(*buf)->grp = ft_strdup(grp->gr_name);
	(*buf)->attr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if ((acl = acl_get_file((*buf)->lnk ? (*buf)->lnk
		: path, ACL_TYPE_EXTENDED)))
	{
		(*buf)->acl = 1;
		acl_free((void*)acl);
	}
}

void	bad_options(char **av, int i, int j)
{
	if ((i && !ft_strrchr("-GlrRat", av[j][i]))
			|| ((av[j][2] && av[j][1] == '-')))
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(av[j][i]);
		ft_putstr("\nusage: ls [-aGlrRt] [file ...]\n");
		exit(EXIT_FAILURE);
	}
}
