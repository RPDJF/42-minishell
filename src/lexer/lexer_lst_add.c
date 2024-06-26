/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:30 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:30 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*req_wildcard(char *str, bool is_quoted)
{
	char	*cursor;

	if (!is_quoted || !str)
		return (str);
	cursor = str;
	while (*cursor)
	{
		if (*cursor == '*')
			*cursor = 5;
		cursor++;
	}
	return (str);
}

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
		neww->prev = tmp;
	}
}

t_word	*tword_new(char *cmd, bool var, bool is_quoted)
{
	t_word	*p;

	p = ft_calloc(1, sizeof(t_cmd));
	if (!p)
		crash_exit();
	p->str = req_wildcard(cmd, is_quoted);
	p->is_var = var;
	p->is_quoted = is_quoted;
	p->next = NULL;
	return (p);
}
