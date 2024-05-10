/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst_add_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:27:02 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/10 16:33:53 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	**token_add_back(t_token **token, t_token *newww)
{
	t_token	*tmp;

	if (!token || !newww)
		return (NULL);
	if (!*token)
		*token = newww;
	else
	{
		tmp = *token;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = newww;
		newww->prev = tmp;
	}
	return (token);
}

int	syntax_redir_delem(t_tlex *word)
{
	if (word && word->next)
		if (tw_is_delem(word->cmd) == 2 && tw_is_delem(word->next->cmd) == 1)
			return (0);
	return (1);
}

int	pars_arg_tk_cmd(t_token *neww, t_cmd *token, t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->tmp1)
	{
		if (!syntax_redir_delem(pars->tmp1)
			||tw_is_delem(pars->tmp1->cmd) == 1
			|| !tk_delem_syntax(pars->tmp1->cmd, false))
			break ;
		else if (tw_is_delem(pars->tmp1->cmd) == 2)
		{
			if (!token_add_back(&neww, newwtk_delem(pars->tmp1->cmd, pars)))
				return (0);
		}
		else
		{
			token->argv[i] = pars->tmp1->cmd;
			i++;
			pars->tmp1 = pars->tmp1->next;
		}
	}
	token->argc = i;
	return (1);
}
