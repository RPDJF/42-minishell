/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:41 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/09 15:56:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_executor	*init_executor(t_token *tokens)
{
	t_executor	*executor;

	executor = galloc(sizeof(t_executor));
	if (!executor)
		crash_exit();
	executor->og_fd_in = dup(STDIN_FILENO);
	if (executor->og_fd_in < 0)
		crash_exit();
	executor->og_fd_out = dup(STDOUT_FILENO);
	if (executor->og_fd_out < 0)
		crash_exit();
	executor->has_pipe = has_pipe(tokens);
	executor->tokens = tokens;
	init_context(executor);
	return (executor);
}

static void	and_or(t_executor *exec, t_token **tokens)
{
	t_token			*cmd;
	int				status;

	cmd = find_last_cmd(exec, *tokens);
	if (cmd)
		status = wait_token(cmd);
	else
		status = 0;
	update_exitcode(status);
	if ((*tokens)->type == token_and)
	{
		if (status)
			while (*tokens && (*tokens)->type != token_or)
				*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == token_or)
	{
		if (!status)
			while (*tokens && (*tokens)->type != token_and)
				*tokens = (*tokens)->next;
	}
}

static void	exec_token(t_executor *exec, t_token **tokens)
{
	if ((*tokens)->type == token_pipe)
	{
		(*tokens) = (*tokens)->next;
		return ;
	}
	else if ((*tokens)->type == token_cmd)
		init_child(*tokens);
	else if ((*tokens)->type == token_var)
		exec_var_init(exec, *tokens);
	else if ((*tokens)->type == token_and || (*tokens)->type == token_or)
		and_or(exec, tokens);
	else if ((*tokens)->type == token_subshell)
		init_subshell(*tokens);
	if (*tokens
		&& !((*tokens)->type == token_stdin || (*tokens)->type == token_stdout))
		(*tokens) = (*tokens)->next;
	while ((*tokens)
		&& ((*tokens)->type == token_stdin || (*tokens)->type == token_stdout))
		(*tokens) = (*tokens)->next;
}

int	executor(t_token *tokens)
{
	t_executor	*executor;

	executor = init_executor(tokens);
	set_interactive(false);
	while (get_minishell()->sigint == 0 && tokens)
	{
		exec_redir(tokens->context, tokens);
		exec_token(executor, &tokens);
	}
	if (get_minishell()->sigint == SIGINT)
		exit_signint(executor, get_minishell()->sigint);
	else
		wait_all_tokens(executor->tokens);
	set_interactive(true);
	get_minishell()->sigint = 0;
	get_minishell()->cur_pid = 0;
	close_all_fd(executor->context);
	return (get_exitcode());
}
