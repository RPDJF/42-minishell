#include "executor.h"

static t_context	*init_context(t_executor *executor)
{
	t_context	*context;

	context = ft_calloc(1, sizeof(t_context));
	if (!context)
		crash_exit();
	context->has_pipe = &executor->has_pipe;
	context->og_fd_in = &executor->og_fd_in;
	context->og_fd_out = &executor->og_fd_out;
	context->fd_in = STDIN_FILENO;
	context->fd_out = STDOUT_FILENO;
	return (context);
}

static t_executor	*init_executor(t_token *tokens)
{
	t_executor	*executor;
	t_context	**context;

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
	context = &executor->context;
	while (tokens)
	{
		*context = init_context(executor);
		if (!*context)
			crash_exit();
		context = &(*context)->next;
		tokens = tokens->next;
	}
	return (executor);
}

static void	update_status_var(int status)
{
	char	*status_str;

	if (get_minishell()->sigint != SIGINT)
		status_str = ft_itoa(status);
	else
		status_str = ft_strdup("130");
	if (!status_str)
		crash_exit();
	update_var(new_var("?", status_str, false, false));
}

static void	exec_token(t_executor *exec, t_context *context, t_token **tokens)
{
	if ((*tokens)->type == token_pipe)
	{
		(*tokens) = (*tokens)->next;
		return ;
	}
	else if ((*tokens)->type == token_cmd)
	{
		init_child(context, *tokens);
		if (context->fd_in != STDIN_FILENO)
			close(context->fd_in);
		if (context->fd_out != STDOUT_FILENO)
			close(context->fd_out);
	}
	else if ((*tokens)->type == token_var)
		exec_var_init(exec, *tokens);
	(*tokens) = (*tokens)->next;
}

void	executor(t_token *tokens)
{
	t_executor	*executor;
	t_context	*context;

	executor = init_executor(tokens);
	context = executor->context;
	if (executor->has_pipe)
		exec_pipe(executor, tokens);
	exec_redir(executor, tokens);
	get_minishell()->is_interactive = false;
	while (get_minishell()->sigint != SIGINT && tokens)
	{
		if (tokens->type == token_pipe)
			context = context->next;
		exec_token(executor, context, &tokens);
	}
	if (get_minishell()->sigint == SIGINT)
	{
		exit_signint(executor);
		get_minishell()->sigint = 0;
	}
	else
		update_status_var(wait_tokens(executor));
	get_minishell()->is_interactive = true;
}
