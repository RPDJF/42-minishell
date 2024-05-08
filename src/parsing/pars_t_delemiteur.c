/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_t_delemiteur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:47 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:48 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tk_delem(t_token *neww, t_pars *pars)
{
	if (!pars->tmp1->cmd->is_quoted && !pars->tmp1->cmd->next)
	{
		if (!ft_strcmp(pars->tmp1->cmd->str, "|"))
		{
			neww->type = token_pipe;
			neww->data = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
			if (!neww->data)
				crash_exit();
			pars->tmp1 = pars->tmp1->next;
			return (1);
		}
		else if (!ft_strcmp(pars->tmp1->cmd->str, "||"))
		{
			neww->type = token_or;
			pars->tmp1 = pars->tmp1->next;
			return (1);
		}
		else if (!ft_strcmp(pars->tmp1->cmd->str, "&&"))
		{
			neww->type = token_and;
			pars->tmp1 = pars->tmp1->next;
			return (1);
		}
	}
	return (0);
}

int	tw_is_delem(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '|' && !cmd->str[1])
			|| (cmd->str[0] == '|' && cmd->str[1] == '|' && !cmd->str[2])
			|| (cmd->str[0] == '&' && cmd->str[1] == '&' && !cmd->str[2])
			|| (cmd->str[0] == ')' && !cmd->is_quoted && !cmd->next
				&& !cmd->prev)))
		return (1);
	else if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '<' && !cmd->str[1])
			|| (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			|| (cmd->str[0] == '>' && !cmd->str[1])
			|| (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])))
		return (2);
	return (0);
}

t_token_type	define_type(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next)
	{
		if (cmd->str[0] == '<' && !cmd->str[1])
			return (token_stdin);
		if (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			return (token_stdin);
		if (cmd->str[0] == '>' && !cmd->str[1])
			return (token_stdout);
		if (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])
			return (token_stdout);
	}
	return (0);
}
