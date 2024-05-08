/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_var_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:36 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:36 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	has_command(t_token *tokens)
{
	while (tokens && tokens->type != token_pipe
		&& tokens->type != token_and && tokens->type != token_or)
	{
		if (tokens->type == token_cmd)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

void	exec_var_init(t_executor *executor, t_token *token)
{
	t_var_init	*var_init;
	t_var		*var;

	if (has_command(token) || executor->has_pipe)
		return ;
	var_init = (t_var_init *)token->data;
	var = new_var(var_init->name,
			parse_words(var_init->value), false, false);
	update_var(var);
}
