/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:13 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:20:05 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

t_garbcol	**getgarbage(void)
{
	static t_garbcol	*collector;

	return (&collector);
}

void	gfree(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*todel;

	collector = getgarbage();
	todel = *collector;
	while (todel && todel->content != address)
		todel = todel->next;
	if (!todel)
		free(address);
	else
	{
		if (todel->previous)
			todel->previous->next = todel->next;
		else
			*collector = todel->next;
		if (todel->next)
			todel->next->previous = todel->previous;
		free(todel->content);
		free(todel);
	}
	return ;
}

void	*addgarbage(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*tmp;
	t_garbcol	*last;

	if (!address)
		return (0);
	collector = getgarbage();
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
		return (0);
	last = 0;
	tmp->next = 0;
	tmp->previous = 0;
	tmp->content = address;
	if (*collector)
	{
		last = lastgarbage(*collector);
		last->next = tmp;
		tmp->previous = last;
	}
	else
		*collector = tmp;
	return (tmp->content);
}

void	*galloc(size_t size)
{
	return (addgarbage(malloc(size)));
}

void	cleargarbage(void)
{
	t_garbcol	**collector;
	t_garbcol	*todel;
	t_garbcol	*tmp;

	collector = getgarbage();
	todel = *collector;
	while (todel)
	{
		free(todel->content);
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	*collector = 0;
}
