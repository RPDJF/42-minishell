#include "executor.h"

static int	start_subshell(t_token *tokens)
{
	t_subshell	*subshell;

	subshell = (t_subshell *)tokens->data;
	if (tokens->context->fd_in != STDIN_FILENO
		&& tokens->context->fd_in >= 0)
	{
		dup2(tokens->context->fd_in, STDIN_FILENO);
		close(tokens->context->fd_in);
	}
	if (tokens->context->fd_out != STDOUT_FILENO
		&& tokens->context->fd_out >= 0)
	{
		dup2(tokens->context->fd_out, STDOUT_FILENO);
		close(tokens->context->fd_out);
	}
	close_all_fd(tokens->context);
	return (executor(subshell->token));
}

pid_t	init_subshell(t_token *tokens)
{
	t_subshell	*subshell;

	subshell = (t_subshell *)tokens->data;
	subshell->pid = fork();
	if (subshell->pid < 0)
		crash_exit();
	if (subshell->pid == 0)
		exit(start_subshell(tokens));
	if (tokens->context->fd_in != STDIN_FILENO)
		close(tokens->context->fd_in);
	if (tokens->context->fd_out != STDOUT_FILENO)
		close(tokens->context->fd_out);
	return (subshell->pid);
}
