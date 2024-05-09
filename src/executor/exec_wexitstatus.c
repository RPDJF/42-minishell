/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wexitstatus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:38 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/09 15:55:51 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_exitcode(void)
{
	t_var	*exit;

	exit = get_var("?");
	if (exit && exit->value)
		return (ft_atoi(exit->value));
	return (0);
}

static int	get_wexistatus(int status)
{
	t_var	*exit;

	exit = get_var("?");
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		update_exitcode(status);
	}
	else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status) + 128;
		update_exitcode(status);
	}
	else
		return (get_exitcode());
	return (status);
}

int	wait_token(t_token *token)
{
	int	status;

	if (token->type == token_cmd)
	{
		if (((t_cmd *)token->data)->pid && !((t_cmd *)token->data)->status)
		{
			waitpid(((t_cmd *)token->data)->pid, &status, 0);
			((t_cmd *)token->data)->status = get_wexistatus(status);
			return (((t_cmd *)token->data)->status);
		}
		return (((t_cmd *)token->data)->status);
	}
	else if (token->type == token_subshell)
	{
		if (((t_subshell *)token->data)->pid
			&& !((t_subshell *)token->data)->status)
		{
			waitpid(((t_subshell *)token->data)->pid, &status, 0);
			((t_subshell *)token->data)->status = get_wexistatus(status);
			return (((t_subshell *)token->data)->status);
		}
		return (((t_subshell *)token->data)->status);
	}
	return (get_exitcode());
}

int	wait_all_tokens(t_token *tokens)
{
	t_var	*exit;
	int		status;

	exit = get_var("?");
	if (exit && exit->value)
		status = ft_atoi(exit->value);
	else
		status = 0;
	while (tokens)
	{
		if (tokens->type == token_cmd || tokens->type == token_subshell
			|| tokens->type == token_var)
			status = wait_token(tokens);
		tokens = tokens->next;
	}
	return (status);
}
