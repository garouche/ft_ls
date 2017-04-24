/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:55:09 by garouche          #+#    #+#             */
/*   Updated: 2017/04/22 15:43:56 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	file_type(t_ls **lst)
{
	if (S_ISREG((*lst)->st.st_mode))
		return ('-');
	else if (S_ISDIR((*lst)->st.st_mode))
		return ('d');
	else if (S_ISCHR((*lst)->st.st_mode))
		return ('c');
	else if (S_ISBLK((*lst)->st.st_mode))
		return ('b');
	else if (S_ISFIFO((*lst)->st.st_mode))
		return ('p');
	else if (S_ISLNK((*lst)->st.st_mode))
		return ('l');
	else if (S_ISSOCK((*lst)->st.st_mode))
		return ('s');
	return (0);
}

char	x_right(t_ls **lst, char mode)
{
	int	id;
	int	x;

	x = 0;
	id = 0;
	if (mode == 0 || mode == 1)
	{
		x = mode ? S_IXGRP & (*lst)->st.st_mode : S_IXUSR & (*lst)->st.st_mode;
		id = mode ? S_ISGID & (*lst)->st.st_mode : S_ISUID & (*lst)->st.st_mode;
		if (x && id)
			return ('s');
		else if (!x && id)
			return ('S');
	}
	else if (mode == 2)
	{
		id = S_ISVTX & (*lst)->st.st_mode;
		x = S_IXOTH & (*lst)->st.st_mode;
		if (x && id)
			return ('t');
		else if (!x && id)
			return ('T');
	}
	return (x ? 'x' : '-');
}

char	*user_right(t_ls **lst)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = ft_memalloc(sizeof(char) * 13)))
		exit(EXIT_FAILURE);
	str[0] = file_type(lst);
	str[1] = S_IRUSR & (*lst)->st.st_mode ? 'r' : '-';
	str[2] = S_IWUSR & (*lst)->st.st_mode ? 'w' : '-';
	str[3] = x_right(lst, 0);
	str[4] = S_IRGRP & (*lst)->st.st_mode ? 'r' : '-';
	str[5] = S_IWGRP & (*lst)->st.st_mode ? 'w' : '-';
	str[6] = x_right(lst, 1);
	str[7] = S_IROTH & (*lst)->st.st_mode ? 'r' : '-';
	str[8] = S_IWOTH & (*lst)->st.st_mode ? 'w' : '-';
	str[9] = x_right(lst, 2);
	str[10] = (*lst)->attr > 0 ? '@' : ' ';
	str[10] = str[10] == ' ' && (*lst)->acl == 1 ? '+' : str[10];
	str[11] = ' ';
	return (str);
}

char	*str_lnk(t_ls **lst, t_max *max)
{
	char	*str;
	char	*buf;
	int		i;

	if (!(str = malloc(sizeof(char) * max->lnk + 2)))
		exit(EXIT_FAILURE);
	ft_memset(str, ' ', max->lnk + 2);
	buf = ft_itoa((*lst)->st.st_nlink);
	i = ft_strlen(buf);
	ft_memcpy(&str[max->lnk - i], buf, i);
	str[max->lnk + 1] = 0;
	free(buf);
	return (str);
}

int		l_flag(t_ls **lst, t_max *max)
{
	char	*str;

	str = ft_memalloc(32 + max->lnk + max->usrname + max->grpname + max->size);
	if (!str)
		exit(EXIT_FAILURE);
	cat_and_free(&str, user_right(lst));
	cat_and_free(&str, str_lnk(lst, max));
	cat_and_free(&str, str_usr(lst, max));
	cat_and_free(&str, str_grp(lst, max));
	cat_and_free(&str, str_size(lst, max));
	cat_and_free(&str, str_time(lst));
	ft_putstr(str);
	free(str);
	return (0);
}
