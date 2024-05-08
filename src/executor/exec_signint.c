/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:24 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:24 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exit_signint(t_executor *executor)
{
	t_token		*tokens;
	t_context	*context;

	tokens = executor->tokens;
	context = executor->context;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			if (((t_cmd *)tokens->data)->pid)
				kill(((t_cmd *)tokens->data)->pid, SIGINT);
		}
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
}
