/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:13 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/26 02:21:29 by rude-jes         ###   ########.fr       */
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
	t_garbcol	*tmp;
	t_garbcol	*prev;

	if (!address)
		return ;
	collector = getgarbage();
	tmp = *collector;
	prev = 0;
	while (tmp)
	{
		if (tmp->content == address)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*collector = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	*addgarbage(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*tmp;

	if (!address)
		return (0);
	collector = getgarbage();
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
		return (0);
	if (*collector)
		tmp->next = (*collector);
	else
		tmp->next = 0;
	tmp->content = address;
	*collector = tmp;
	return (address);
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
