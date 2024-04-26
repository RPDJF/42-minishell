#include "executor.h"

static int	start_subshell(t_token *tokens)
{
	t_subshell	*subshell;
	int			fd[2];

	subshell = (t_subshell *)tokens->data;
	fd[0] = tokens->context->fd_in;
	fd[1] = tokens->context->fd_out;
	dup2(fd[1], STDOUT_FILENO);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	while (tokens->context)
	{
		if (tokens->context->fd_in != STDIN_FILENO)
			close(tokens->context->fd_in);
		tokens->context = tokens->context->next;
	}
	return (executor(subshell->token, fd));
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
