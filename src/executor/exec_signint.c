#include "executor.h"

void	exit_signint(t_executor *executor)
{
	t_token	*tokens;

	tokens = executor->tokens;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			if (((t_cmd *)tokens->data)->pid)
				kill(((t_cmd *)tokens->data)->pid, SIGINT);
		}
		tokens = tokens->next;
	}
	if (executor->fd_in != STDIN_FILENO)
		close(executor->fd_in);
	if (executor->fd_out != STDOUT_FILENO)
		close(executor->fd_out);
	if (executor->fd_in_pipe)
		close(executor->fd_in_pipe);
}
