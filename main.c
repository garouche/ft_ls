/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:01:52 by garouche          #+#    #+#             */
/*   Updated: 2017/02/22 17:49:52 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <time.h>
#include <sys/xattr.h>
#include <errno.h>
#include <string.h>

void	roll(t_dir **dir, t_dir **buf, t_ls **ls, t_opt **opt)
{
	char *str;
	int sort;

	if (*buf == NULL)
	{
		*buf = malloc(sizeof(t_dir));
		set_path(dir, buf, ls);
		(*buf)->next = NULL;
	}
	else if (sort_type(buf, opt, ls) > 0)
		push_back_dir(dir, buf, ls, opt);
	else
		push_front_dir(dir, buf, ls);
}

void	display(t_dir **dir, t_opt **opt, t_ls **ls)
{
	char *file_path;
	t_dir *buf;
	int i;

	i = 0;
	buf = NULL;
	file_path = ft_strjoin((*dir)->dir_name, "/");
	if ((*dir)->path)
	{
		while (((*ls)->dir = readdir((*dir)->path)))
		{
			if (*(*ls)->dir->d_name != '.' || (*opt)->a == 1)
			{
				display_file(file_path, ls);
				if ((S_ISDIR ((*ls)->st->st_mode) && (*opt)->R == 1 && (*opt)->a == 0)
				||	((S_ISDIR ((*ls)->st->st_mode) && (*opt)->R == 1) && i >= 2))
					roll(dir, &buf, ls, opt);
			}
			i++;
		}
		closedir((*dir)->path);
	}
	cat_list(dir, &buf);
	free(file_path);
}

int main (int argc, char **argv)
{
	t_dir 	*dir;
	t_opt	*opt;
	char 	*start;
	t_ls	*ls;

	ls = malloc(sizeof(t_ls));
	ls->st = malloc(sizeof(struct stat));
	ls->dir = NULL;	
	set_opt(&opt, argc, argv);
	while (set_dir(&dir, argc, argv, &ls))
	{
		if (dir->path)
		{
			if (dir)
			{
				if (ft_strchr(dir->dir_name, '/') == NULL)
					dir->start = ft_strjoin(dir->dir_name, "/");
				else
					dir->start = ft_strjoin(dir->dir_name, "");
			}
			while (dir)
			{
				if (ft_strcmp(dir->start, dir->dir_name) != 0)
					printf("%s:\n", dir->dir_name);
				display(&dir, &opt, &ls);
				if ((dir = dir->next) != NULL)
					printf("	\n\n");
			}
		}
	}
	free(ls->st);
	free(ls);
	free(opt);
//	printf("%s \n", dir->next->dir->d_name);
//	dir = dir->next;
//	if (ac == 1)
//	{
//		while ((ok = readdir(path)))
///		{
///			if (*ok->d_name != '.')
//			{
//				printf("%s	",ok->d_name);
///				bufpath = ft_strjoin("./", ok->d_name);
//				stat(bufpath, st);
//				printf("%d gid	", (S_ISVTX & st->st_mode));
///				printf("%u %d  %d",st->st_uid, major (st->st_dev), minor (st->st_dev));
//				printf("	%lld  %d", st->st_size, st->st_blksize);
//				printf("	%d  %d ", S_IRWXO & st->st_mode, st->st_nlink);
//				printf("	|%zd\n", listxattr(bufpath, NULL, 0, 0));
//				free(bufpath);
//			}
//		}
		
//	}
	return (0);
}

