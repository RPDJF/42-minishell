/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst_add_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:27:02 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 17:49:59 by ilyanar          ###   ########.fr       */
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

int	pars_arg_tk_cmd(t_token *neww, t_cmd *token, t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->tmp1)
	{
		if (tw_is_delem(pars->tmp1->cmd) == 1
			|| !tk_delem_syntax(pars->tmp1->cmd, false))
			break ;
		if (pars->tmp1->next && !syntax_redirection(pars->tmp1->next->cmd))
			return (0);
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
