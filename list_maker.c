/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:33:23 by garouche          #+#    #+#             */
/*   Updated: 2017/02/21 18:20:25 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*push_back_dir(t_dir **dir, t_dir **buf, t_ls **ls)
{
	t_dir	*ptr;
	t_dir	*ptr2;

	ptr = *buf;
	while (ptr->next &&
	ft_strcmp((*ls)->dir->d_name, ft_strrchr(ptr->next->dir_name, '/') + 1)
   	> 0)
		ptr = ptr->next;
	if (ptr->next == NULL)
	{
		if ((ptr->next = malloc(sizeof(t_dir))) == NULL)
			return (NULL);
		set_path(dir, &ptr->next, ls);
		ptr->next->next = NULL;
	}
	else if (ptr->next != NULL)
	{
		ptr2 = malloc(sizeof(t_dir));
		ptr2->next = ptr->next;
		ptr->next = ptr2;
		set_path(dir, &ptr2, ls);
	}
	return (ptr);
}

t_dir	*push_front_dir(t_dir **dir, t_dir **buf, t_ls **ls)
{
	t_dir *ptr;
	t_dir *ptr2;
	char	*str;
	
	if ((ptr2 = malloc(sizeof(t_dir))) == NULL)
		return (NULL);
	ptr2->next = *buf;
	*buf = ptr2;
	ptr = *buf;
	set_path(dir, &ptr, ls);
	return (ptr);	
}
