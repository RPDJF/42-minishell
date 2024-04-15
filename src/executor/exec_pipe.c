#include "executor.h"

static int	init_pipe(t_executor *executor, t_pipe *pipes)
{
	if (pipe(pipes->pipe) < 0)
		crash_exit();
	executor->fd_out = pipes->pipe[1];
	executor->fd_in_pipe = pipes->pipe[0];
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

int	exec_pipe(t_executor *executor, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == token_pipe)
		{
			init_pipe(executor, (t_pipe *)tokens->data);
			break ;
		}
		tokens = tokens->next;
	}
	return (0);
}
