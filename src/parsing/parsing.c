/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:53 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/09 18:30:05 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

t_token	*token_new_end(t_token *neww, t_pars *pars)
{
	if (tw_strchr(pars->tmp1->cmd, '=') && var_quoted(pars->tmp1->cmd)
		&& correct_syntax_var(pars->tmp1->cmd->str))
	{
		if (!tk_is_var_init(neww, pars))
			return (NULL);
		return (neww);
	}
	else if (tw_is_delem(pars->tmp1->cmd) == 1)
	{
		if (!tk_delem(neww, pars))
			return (NULL);
		return (neww);
	}
	else if (is_subshell(pars->tmp1->cmd) == 1)
	{
		if (!tk_subshell(neww, pars))
			return (NULL);
		return (neww);
	}
	return (NULL);
}

t_token	*token_new(t_pars *pars)
{
	t_token	*neww;

	neww = NULL;
	if (tw_is_delem(pars->tmp1->cmd) == 2)
	{
		if (pars->tmp1->next
			&& !syntax_redirection(pars->tmp1->next->cmd, true))
			return (NULL);
		if (!token_add_back(&neww, newwtk_delem(pars->tmp1->cmd, pars)))
			return (NULL);
	}
	else
	{
		if (!tk_delem_syntax(pars->tmp1->cmd, true))
			return (NULL);
		neww = ft_calloc(1, sizeof(t_token));
		if (!neww)
			crash_exit();
		if (!token_new_end(neww, pars))
		{
			if (!tk_cmd(neww, pars))
				return (NULL);
		}
	}
	return (neww);
}

t_token	*parsing(t_tlex **lex)
{
	t_token	*token;
	t_token	*neww;
	t_pars	pars;

	token = NULL;
	ft_bzero(&pars, sizeof(t_pars));
	pars.tmp1 = *lex;
	while (pars.tmp1)
	{
		neww = token_new(&pars);
		if (!neww)
			return (NULL);
		token_add_back(&token, neww);
		if (!check_syntax_subshell(token) || !token_syntax(token))
			return (NULL);
	}
	if (!syntax_at_end(token))
		return (free_exit_token(&token, lex));
	return (token);
}
