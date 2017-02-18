/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:01:52 by garouche          #+#    #+#             */
/*   Updated: 2017/02/18 21:39:11 by garouche         ###   ########.fr       */
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

void	roll(t_dir **dir, char *start, t_dir **buf)
{
	t_dir *ptr;
	char *str;	
	if (*buf == NULL)
	{
		*buf = malloc(sizeof(t_dir));
		str = (ft_strcmp(start, (*dir)->dir_name) == 0 ? "" : "/");
		str = ft_strjoin((*dir)->dir_name, str);
		(*buf)->dir_name = ft_strjoin(str, (*dir)->dir->d_name);
		free(str);
		(*buf)->path = opendir((*buf)->dir_name);
		(*buf)->next = NULL;
	}
	else
	{
		ptr = *buf;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_dir));
		ptr = ptr->next;
		ptr->dir_name = ft_strjoin((*dir)->dir_name, (*dir)->dir->d_name);
		ptr->path = opendir(ptr->dir_name);
		ptr->next = NULL;
	}
}

void	cat_list(t_dir **dir, t_dir **buf)
{
	t_dir	*ptr;
	t_dir 	*ptr2;

	if ((*dir)->next == NULL && *buf)
		(*dir)->next = *buf;
	else if (*buf)
	{
		ptr2 = *buf;
		while (ptr2->next)
			ptr2 = ptr2->next;
		ptr2->next = (*dir)->next;
		(*dir)->next = *buf;	
	}
}
void	display(t_dir **dir, char *start, t_opt **opt)
{
	t_ls	*ls;
	char *file_path;
	char *ptr;
	t_dir *buf;

	buf = NULL;
	file_path = ft_strjoin((*dir)->dir_name, "/");
	ls = malloc(sizeof(t_ls));
	ls->st = malloc(sizeof(struct stat));
	while (((*dir)->dir = readdir((*dir)->path)))
	{
		if (*(*dir)->dir->d_name != '.')
		{
			printf("%s	", (*dir)->dir->d_name);
			ptr = ft_strjoin(file_path, (*dir)->dir->d_name);
			stat(ptr, ls->st);
			free(ptr);
			if (S_ISDIR (ls->st->st_mode) && (*opt)->R == 1)
				roll(dir, start, &buf);
		}
	}
	cat_list(dir, &buf);
	while (buf)
	{
		printf("%s dir_name\n", buf->dir_name);
		buf = buf->next;
	}
	free(ls->st);
	free(ls);
	free(file_path);
}

void	set_opt(t_opt **opt, int ac, char **av)
{
	int i;

	i = 0;
	*opt = malloc(sizeof(t_opt));
	(*opt)->l = 0;
	(*opt)->r = 0;
	(*opt)->R = 0;
	(*opt)->a = 0;
	(*opt)->t = 0;
	if (ac > 1 && av[1][0] == '-')
	{
		while (av[0][i])
		{
			(*opt)->l = (av[1][i] == 'l' ? 1 : (*opt)->l);
			(*opt)->r = (av[1][i] == 'r' ? 1 : (*opt)->r);
			(*opt)->R = (av[1][i] == 'R' ? 1 : (*opt)->R);
			(*opt)->a = (av[1][i] == 'a' ? 1 : (*opt)->a);
			(*opt)->t = (av[1][i] == 't' ? 1 : (*opt)->t);
			i++;
		}
	}
}
	
void	set_dir(t_dir **dir, int ac, char **av)
{
	*dir = malloc(sizeof(t_dir));

	(*dir)->path = opendir("..");
	(*dir)->dir_name = "../";
	(*dir)->next = NULL;

}
int main (int argc, char **argv)
{
	t_dir 	*dir;
	t_opt	*opt;
	char 	*start;
	
	set_opt(&opt, argc, argv);
	set_dir(&dir, argc, argv);
	start = "../";

	while (dir)
	{
		if (ft_strcmp(start, dir->dir_name) != 0)
			printf("%s:\n", dir->dir_name);
		display(&dir, start, &opt);
		printf("\n\n");
		dir = dir->next;
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

