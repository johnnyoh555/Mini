/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooh <jooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:43:57 by jooh              #+#    #+#             */
/*   Updated: 2023/10/11 18:23:14 by jooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy_head;
	t_list	*newlist;
	void	*fcontent;

	if (!lst || !f || !del)
		return (0);
	cpy_head = 0;
	while (lst)
	{
		fcontent = f(lst->content);
		newlist = ft_lstnew(fcontent);
		if (newlist == 0)
		{
			ft_lstclear(&cpy_head, del);
			del (fcontent);
			return (0);
		}
		ft_lstadd_back(&cpy_head, newlist);
		lst = lst->next;
	}
	return (cpy_head);
}
