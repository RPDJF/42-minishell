/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:10 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:27:22 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	count_context(t_token *tokens)
{
	size_t	count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == token_pipe
			|| tokens->type == token_and || tokens->type == token_or)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static t_context	*new_context(t_executor *executor)
{
	t_context	*context;

	context = ft_calloc(1, sizeof(t_context));
	context->has_pipe = &executor->has_pipe;
	context->og_fd_in = &executor->og_fd_in;
	context->og_fd_out = &executor->og_fd_out;
	context->fd_in = STDIN_FILENO;
	context->fd_out = STDOUT_FILENO;
	context->next = 0;
	context->prev = 0;
	return (context);
}

static void	init_fd_dup(t_executor *executor)
{
	t_token			*tokens;
	t_context		*context;
	t_token_type	type;

	context = executor->context;
	tokens = executor->tokens;
	while (tokens)
	{
		type = tokens->type;
		if (type == token_pipe)
			exec_pipe(context, tokens);
		if (type == token_pipe || type == token_and || type == token_or)
			context = context->next;
		else if (type == token_stdin)
			exec_here_doc(context, tokens);
		tokens->context = context;
		tokens = tokens->next;
	}
}

t_context	*init_context(t_executor *executor)
{
	t_context	*context;
	size_t		count;

	context = new_context(executor);
	executor->context = context;
	count = count_context(executor->tokens);
	while (--count, count > 0)
	{
		context->next = new_context(executor);
		context->next->prev = context;
		context = context->next;
	}
	init_fd_dup(executor);
	return (executor->context);
}
