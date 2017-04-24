/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_flag2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 19:10:26 by garouche          #+#    #+#             */
/*   Updated: 2017/04/21 18:13:47 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*str_usr(t_ls **lst, t_max *max)
{
	char *str;
	char *buf;

	if (!(str = malloc(sizeof(char) * max->usrname + 3)))
		exit(EXIT_FAILURE);
	ft_memset(str, ' ', max->usrname + 2);
	if ((*lst)->usr)
		ft_memcpy(str, (*lst)->usr, ft_strlen((*lst)->usr));
	else
	{
		buf = ft_itoa((*lst)->st.st_uid);
		ft_memcpy(str, buf, ft_strlen(buf));
		free(buf);
	}
	str[max->usrname + 2] = 0;
	return (str);
}

char	*str_grp(t_ls **lst, t_max *max)
{
	char *str;
	char *buf;

	if (!(str = malloc(sizeof(char) * max->grpname + 3)))
		exit(EXIT_FAILURE);
	ft_memset(str, ' ', max->grpname + 2);
	if ((*lst)->grp)
		ft_memcpy(str, (*lst)->grp, ft_strlen((*lst)->grp));
	else
	{
		buf = ft_itoa((*lst)->st.st_gid);
		ft_memcpy(str, buf, ft_strlen(buf));
		free(buf);
	}
	str[max->grpname + 2] = 0;
	return (str);
}

char	*str_dev(t_ls **lst, t_max *max)
{
	int		i;
	int		j;
	char	*str;
	char	*buf;

	i = max->size;
	if (!(str = malloc(sizeof(char) * i)))
		exit(EXIT_FAILURE);
	ft_memset(str, ' ', max->size);
	if (!(buf = ft_itoa(minor((*lst)->st.st_rdev))))
		exit(EXIT_FAILURE);
	j = ft_strlen(buf);
	ft_memcpy(&str[i - (j + 1)], buf, j);
	free(buf);
	if (!(buf = ft_itoa(major((*lst)->st.st_rdev))))
		exit(EXIT_FAILURE);
	j = ft_strlen(buf);
	ft_memcpy(&str[1 + max->major - j], buf, j);
	free(buf);
	str[1 + max->major] = ',';
	str[max->size] = 0;
	return (str);
}

char	*str_size(t_ls **lst, t_max *max)
{
	char	*str;
	char	*buf;
	int		i;

	if ((!S_ISBLK((*lst)->st.st_mode) && !S_ISCHR((*lst)->st.st_mode))
			|| S_ISLNK((*lst)->st.st_mode))
	{
		if (!(str = malloc(max->size + 2)))
			exit(EXIT_FAILURE);
		ft_memset(str, ' ', max->size + 2);
		if (!(buf = ft_itoa((*lst)->st.st_size)))
			exit(EXIT_FAILURE);
		i = ft_strlen(buf);
		ft_memcpy(&str[max->size - (max->device ? i + 1 : i)], buf, i);
		free(buf);
		str[max->device ? max->size : max->size + 1] = 0;
	}
	else
		str = str_dev(lst, max);
	return (str);
}

char	*str_time(t_ls **lst)
{
	char	*str;
	time_t	tloc;
	char	*buf;

	buf = ctime(&(*lst)->st.st_mtimespec.tv_sec);
	if (!(str = malloc(sizeof(char) * 14)))
		exit(EXIT_FAILURE);
	ft_memset(str, ' ', 14);
	if ((*lst)->st.st_mtimespec.tv_sec > (tloc = time(NULL)) ||
	tloc - (*lst)->st.st_mtimespec.tv_sec >= 15778800)
	{
		ft_memcpy(str, &buf[4], 6);
		ft_memcpy(&str[8], &buf[20], 4);
	}
	else
		ft_memcpy(str, &buf[4], 12);
	str[13] = '\0';
	return (str);
}
