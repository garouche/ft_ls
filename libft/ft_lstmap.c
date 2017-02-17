/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 18:50:02 by garouche          #+#    #+#             */
/*   Updated: 2016/11/30 21:54:33 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *buf2;
	t_list *lol;

	if (lst == NULL || f == NULL)
		return (NULL);
	buf2 = f(lst);
	res = ft_lstnew(buf2->content, buf2->content_size);
	lol = res;
	while (lst->next && res)
	{
		lst = lst->next;
		buf2 = f(lst);
		res->next = ft_lstnew(buf2->content, buf2->content_size);
		res = res->next;
	}
	return (lol);
}
