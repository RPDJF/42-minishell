#include "executor.h"

pid_t	init_subshell(t_token *tokens)
{
	t_subshell	*subshell;
	int			fd[2];

	subshell = (t_subshell *)tokens->data;
	subshell->pid = fork();
	if (subshell->pid < 0)
		crash_exit();
	if (subshell->pid == 0)
	{
		fd[0] = tokens->context->fd_in;
		fd[1] = tokens->context->fd_out;
		dup2(fd[1], STDOUT_FILENO);
		while (tokens->context)
		{
			if (tokens->context->fd_in != STDIN_FILENO)
				close(tokens->context->fd_in);
			tokens->context = tokens->context->next;
		}
		exit(executor(subshell->token, fd));
	}
	if (tokens->context->fd_in != STDIN_FILENO)
		close(tokens->context->fd_in);
	if (tokens->context->fd_out != STDOUT_FILENO)
		close(tokens->context->fd_out);
	return (subshell->pid);
}
