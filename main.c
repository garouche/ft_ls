/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:01:52 by garouche          #+#    #+#             */
/*   Updated: 2017/02/21 18:25:09 by garouche         ###   ########.fr       */
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

	if (*buf)
	{
		if ((str = ft_strrchr((*buf)->dir_name, '/') + 1) == NULL)
			str = (*buf)->dir_name + 2;
		sort_type(str, opt, ls);
	}
	if (*buf == NULL)
	{
		*buf = malloc(sizeof(t_dir));
		set_path(dir, buf, ls);
		(*buf)->next = NULL;
	}
	else if (ft_strcmp((*ls)->dir->d_name, str) > 0)
		push_back_dir(dir, buf, ls);
	else
		push_front_dir(dir, buf, ls);
}

void	display(t_dir **dir, t_opt **opt)
{
	t_ls	*ls;
	char *file_path;
	char *ptr;
	t_dir *buf;
	int i;

	i = 0;
	buf = NULL;
	file_path = ft_strjoin((*dir)->dir_name, "/");
	ls = malloc(sizeof(t_ls));
	ls->st = malloc(sizeof(struct stat));
	while ((ls->dir = readdir((*dir)->path)))
	{
		if (*ls->dir->d_name != '.' || (*opt)->a == 1)
		{
			printf("%s	", ls->dir->d_name);
			ptr = ft_strjoin(file_path, ls->dir->d_name);
			lstat(ptr, ls->st);
			free(ptr);
			if ((S_ISDIR (ls->st->st_mode) && (*opt)->R == 1 && (*opt)->a == 0)
			||	((S_ISDIR (ls->st->st_mode) && (*opt)->R == 1) && i >= 2))
				roll(dir, &buf, &ls, opt);
		}
		i++;
	}
	closedir((*dir)->path);
	cat_list(dir, &buf);
	free(ls->st);
	free(ls);
	free(file_path);
}

int main (int argc, char **argv)
{
	t_dir 	*dir;
	t_opt	*opt;
	char 	*start;
	
	set_opt(&opt, argc, argv);
	printf("%d R\n", opt->R);
	set_dir(&dir, argc, argv);
	dir->start = "./";

	while (dir)
	{
		if (ft_strcmp(dir->start, dir->dir_name) != 0)
			printf("%s:\n", dir->dir_name);
		display(&dir, &opt);
		printf("\n\n");
		dir = dir->next;
	}
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

