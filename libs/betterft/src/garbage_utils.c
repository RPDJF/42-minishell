/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 02:44:42 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 03:32:34 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

static bool	free_from_garbcol(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*tmp;
	t_garbcol	*prev;

	collector = getgarbage();
	tmp = *collector;
	prev = 0;
	while (tmp && address)
	{
		if (tmp->content == address)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*collector = tmp->next;
			free(tmp->content);
			free(tmp);
			return (true);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (false);
}

void	gfree(void *address)
{
	if (address && !GARBAGE_COLLECTOR)
		free(address);
	if (!address || !GARBAGE_COLLECTOR)
		return ;
	if (!free_from_garbcol(address))
		free(address);
}

void	cleargarbage(void)
{
	t_garbcol	**collector;
	t_garbcol	*todel;
	t_garbcol	*tmp;

	if (!GARBAGE_COLLECTOR)
		return ;
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
