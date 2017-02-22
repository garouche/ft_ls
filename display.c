/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:40:17 by garouche          #+#    #+#             */
/*   Updated: 2017/02/22 18:15:23 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void	snd_path(char *path, t_ls **ls, char **str)
{
	if ((*ls)->dir != NULL)
		*str = ft_strjoin(path, (*ls)->dir->d_name);
	else
		*str = ft_strjoin("", path);
}

int	display_file(char *path, t_ls **ls)
{
	char *str;
	
	snd_path(path, ls, &str);
	if (lstat(str, (*ls)->st) == -1)
		printf("ls : %s: %s", str, strerror(errno));	
	free(str);
	if ((*ls)->dir != NULL)
		str = (*ls)->dir->d_name;
	else
		str = path;
	printf("%s	", str);
	return (1);
}
