/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:33:23 by garouche          #+#    #+#             */
/*   Updated: 2017/02/21 00:34:00 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*push_back_dir(t_dir **dir, t_dir **buf, char *path, char *start)
{
	t_dir	*ptr;
	t_dir	*ptr2;

	ptr = *buf;
	while (ptr->next
			&& ft_strcmp(path, ft_strrchr(ptr->next->dir_name, '/') + 1) > 0)
		ptr = ptr->next;
	if (ptr->next == NULL)
	{
		if ((ptr->next = malloc(sizeof(t_dir))) == NULL)
			return (NULL);
		set_path(dir, &ptr->next, start, path);
		ptr->next->next = NULL;
	}
	else if (ptr->next != NULL)
	{
		ptr2 = malloc(sizeof(t_dir));
		ptr2->next = ptr->next;
		ptr->next = ptr2;
//		ptr = ptr2;
		set_path(dir, &ptr2, start, path);
	}
	return (ptr);
}

t_dir	*push_front_dir(t_dir **dir, t_dir **buf, char *path, char *start)
{
	t_dir *ptr;
	t_dir *ptr2;
	char	*str;
	
	if ((ptr2 = malloc(sizeof(t_dir))) == NULL)
		return (NULL);
	ptr2->next = *buf;
	*buf = ptr2;
	ptr = *buf;
	set_path(dir, &ptr, start, path);
	return (ptr);	
}
