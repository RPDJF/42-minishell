/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:18 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:18 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	dup_fd(t_context *context)
{
	if (context->fd_in != STDIN_FILENO && context->fd_in >= 0)
	{
		dup2(context->fd_in, STDIN_FILENO);
		close(context->fd_in);
	}
	if (context->fd_out != STDOUT_FILENO && context->fd_out >= 0)
	{
		dup2(context->fd_out, STDOUT_FILENO);
		close(context->fd_out);
	}
	if (context->fd_in < 0 || context->fd_out < 0)
		return (-1);
	return (0);
}

bool	has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == token_pipe)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

void	exec_pipe(t_context *context, t_token *tokens)
{
	if (pipe(((t_pipe *)tokens->data)->pipe))
		crash_exit();
	if (context->fd_out == STDOUT_FILENO)
		context->fd_out = ((t_pipe *)tokens->data)->pipe[1];
	else
		close(((t_pipe *)tokens->data)->pipe[1]);
	context = context->next;
	if (context->fd_in == STDIN_FILENO)
		context->fd_in = ((t_pipe *)tokens->data)->pipe[0];
	else
		close(((t_pipe *)tokens->data)->pipe[0]);
}
