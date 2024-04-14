/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:27:54 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/14 01:05:44 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	tlex_add_back(t_tlex **lst, t_tlex *neww)
{
	t_tlex	*tmp;

	if (!lst || !neww)
		return ;
	if (!*lst)
		*lst = neww;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
		neww->prev = tmp;
	}
}

void	tword_add_back(t_tlex **lst, t_word *neww)
{
	t_word	*tmp;

	if (!lst || !neww)
		return ;
	if (!(*lst)->cmd)
		(*lst)->cmd = neww;
	else
	{
		tmp = (*lst)->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
	}
}

t_word	*tword_new(char *cmd, bool var)
{
	t_word	*p;

	p = calloc(1, sizeof(t_cmd));
	if (!p)
		crash_exit();
	p->str = cmd;
	p->is_var = var;
	p->next = NULL;
	return (p);
}
