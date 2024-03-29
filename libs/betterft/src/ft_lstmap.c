/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:43:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*parent;
	t_list	*child;
	void	*content;

	parent = 0;
	while (lst)
	{
		content = f(lst->content);
		child = ft_lstnew(content);
		if (!child || !child->content)
		{
			del(content);
			if (parent)
				ft_lstclear(&parent, del);
			ft_lstclear(&child, del);
			return (0);
		}
		if (parent)
			ft_lstadd_back(&parent, child);
		else
			parent = child;
		lst = lst->next;
	}
	return (parent);
}
