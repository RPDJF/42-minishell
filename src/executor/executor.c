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

static void	update_status_var(int status)
{
	if (get_minishell()->sigint != SIGINT)
		update_exitcode(status);
	else
		update_exitcode(130);
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
	t_context	*context;

	context = (*tokens)->context;
	if ((*tokens)->type == token_pipe)
	{
		(*tokens) = (*tokens)->next;
		return ;
	}
	else if ((*tokens)->type == token_cmd)
	{
		init_child(*tokens);
		if (context->fd_in != STDIN_FILENO)
			close(context->fd_in);
		if (context->fd_out != STDOUT_FILENO)
			close(context->fd_out);
	}
	else if ((*tokens)->type == token_var)
		exec_var_init(exec, *tokens);
	else if ((*tokens)->type == token_and || (*tokens)->type == token_or)
		and_or(exec, tokens);
	if (*tokens)
		(*tokens) = (*tokens)->next;
}

void	executor(t_token *tokens)
{
	t_executor	*executor;

	executor = init_executor(tokens);
	get_minishell()->is_interactive = false;
	while (get_minishell()->sigint != SIGINT && tokens)
		exec_token(executor, &tokens);
	if (get_minishell()->sigint == SIGINT)
	{
		exit_signint(executor);
		get_minishell()->sigint = 0;
	}
	else
		update_status_var(wait_all_tokens(executor));
	close_all_fd(executor->context);
	get_minishell()->is_interactive = true;
}
