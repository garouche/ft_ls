/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 20:54:28 by garouche          #+#    #+#             */
/*   Updated: 2016/11/30 19:10:16 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *buf;

	buf = *alst;
	while (buf->next)
	{
		*alst = buf->next;
		del(buf->content, buf->content_size);
		buf = *alst;
	}
	del(buf->content, buf->content_size);
	ft_memdel((void**)alst);
}
