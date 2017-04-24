/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:44:51 by garouche          #+#    #+#             */
/*   Updated: 2017/04/22 15:57:30 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		manage_path(char path[1025], t_ls **lst, struct dirent *d)
{
	int i;

	ft_memcpy(path, (*lst)->path, (i = ft_strlen((*lst)->path)) + 1);
	if ((*lst)->path[i - 1] != '/')
	{
		path[i] = '/';
		path[(i += 1)] = 0;
	}
	ft_strcat(&path[i], d->d_name);
	return (1);
}

t_ls	*manage_files_lst(t_opt *opt, char *path, char *name)
{
	t_ls			*buf;

	if (!(buf = init_ls()))
		exit(EXIT_FAILURE);
	lstat(path, &buf->st);
	buf->path = ft_strdup(name);
	if (opt->l)
		l_node(&buf, path);
	return (buf);
}

void	get_max(t_ls *buf, t_max *max)
{
	size_t i;

	i = buf->usr ? ft_strlen(buf->usr) : ft_nblen(buf->st.st_uid);
	max->usrname = i > max->usrname ? i : max->usrname;
	i = buf->grp ? ft_strlen(buf->grp) : ft_nblen(buf->st.st_gid);
	max->grpname = i > max->grpname ? i : max->grpname;
	if ((i = ft_nblen(buf->st.st_size)) > max->size)
		max->size = i;
	if (S_ISBLK(buf->st.st_mode) || S_ISCHR(buf->st.st_mode))
	{
		if ((i = ft_nblen(major(buf->st.st_rdev))) > max->major)
			max->major = i;
		if ((i = ft_nblen(minor(buf->st.st_rdev))) > max->minor)
			max->minor = i;
		max->device = 1;
		max->size = max->major + max->minor + 4;
	}
	else if ((i = ft_nblen(buf->st.st_size)) > max->size && !max->device)
		max->size = i;
	if ((i = ft_nblen(buf->st.st_nlink)) > max->lnk)
		max->lnk = i;
	max->block += buf->st.st_blocks;
}

void	cat_and_free(char **s1, char *s2)
{
	ft_strcat(*s1, s2);
	free(s2);
}

void	manage_dir(t_ls **lst, t_ls **new_dir, t_opt *opt, t_max *max)
{
	char	*str;
	char	*ptr;
	int		i;

	if (opt->l && max->size)
	{
		ptr = ft_itoa(max->block);
		i = ft_strlen(ptr);
		str = ft_memalloc(8 + i);
		if (!ptr || !str)
			exit(EXIT_FAILURE);
		ft_memcpy(str, "total ", 6);
		ft_memcpy(&str[6], ptr, i + 1);
		str[6 + i] = '\n';
		ft_putstr(str);
		free(ptr);
		free(str);
	}
	closedir((*lst)->folder);
	if ((*new_dir)->path && (*lst)->next)
		cat_ls(&(*new_dir), &(*lst)->next);
	else if ((*new_dir)->path)
		(*lst)->next = *new_dir;
	else
		free((*new_dir));
}
