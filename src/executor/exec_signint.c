/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:24 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/09 16:02:32 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	write_raw(int _sigint)
{
	if (_sigint == SIGQUIT)
		ft_putstr_fd("Quit: 3", STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	exit_signint(t_executor *executor, int _sigint)
{
	t_token		*tokens;
	t_context	*context;

	tokens = executor->tokens;
	context = executor->context;
	while (tokens)
	{
		if (tokens->type == token_cmd && ((t_cmd *)tokens->data)->pid)
			kill(((t_cmd *)tokens->data)->pid, _sigint);
		else if (tokens->type == token_subshell
			&& ((t_subshell *)tokens->data)->pid)
			if (((t_subshell *)tokens->data)->pid)
				kill(((t_subshell *)tokens->data)->pid, _sigint);
		tokens = tokens->next;
	}
	while (context)
	{
		if (context->fd_in != STDIN_FILENO && context->fd_in > -1)
			close(context->fd_in);
		if (context->fd_out != STDOUT_FILENO && context->fd_out > -1)
			close(context->fd_out);
		context = context->next;
	}
	write_raw(_sigint);
}
