/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:01:52 by garouche          #+#    #+#             */
/*   Updated: 2017/02/17 23:13:50 by garouche         ###   ########.fr       */
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

void	roll(t_dir **dir)
{
	t_dir *buf;

	if ((*dir)->next == NULL)
	{
		(*dir)->next = malloc(sizeof(t_dir));
		(*dir)->next->next = NULL;
		buf = (*dir)->next;
	}
	else if ((*dir)->next != NULL)
	{
		buf = (*dir)->next;
		while (buf->next)
			buf = buf->next;
		buf->next = malloc(sizeof(t_dir));
		buf = buf->next;
	}
	buf->next = NULL;
	buf->path = opendir((*dir)->dir->d_name);
	buf->dir_name = ft_strjoin((*dir)->dir->d_name, "/");
}

void	display(t_dir **dir)
{
	t_ls	*ls;

	ls = malloc(sizeof(t_ls));
	ls->st = malloc(sizeof(struct stat));
	while (((*dir)->dir = readdir((*dir)->path)))
	{
		if (*(*dir)->dir->d_name != '.')
		{
			printf("%s	", (*dir)->dir->d_name);
			stat(ft_strjoin((*dir)->dir_name, (*dir)->dir->d_name), ls->st);
			if (S_ISDIR (ls->st->st_mode))
				roll(dir);
		}
	}
	free(ls->st);
	free(ls);
}

int main (int ac, char **av)
{
	t_dir 	*dir;
	
	dir = malloc(sizeof(t_dir));
	dir->path = opendir(".");
	dir->dir_name = "./";
	dir->next = NULL;
	while (dir)
	{
		display(&dir);
		printf("\n\n");
		dir = dir->next;
		printf("%s dirname\n", dir->dir_name);
	}

	
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

