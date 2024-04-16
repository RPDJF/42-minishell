#include "executor.h"

// Test needed for this function

static void	switch_fd(t_executor *executor, t_pipe *pipe)
{
	if (executor->fd_in_pipe)
	{
		if (executor->fd_in != STDIN_FILENO)
			close(executor->fd_in);
		executor->fd_in = executor->fd_in_pipe;
		executor->fd_in_pipe = 0;
		close(pipe->pipe[1]);
	}
}

static t_executor	*init_executor(t_token *tokens)
{
	t_executor	*executor;

	executor = galloc(sizeof(t_executor));
	if (!executor)
		crash_exit();
	executor->has_pipe = has_pipe(tokens);
	executor->fd_in = STDIN_FILENO;
	executor->fd_out = STDOUT_FILENO;
	executor->fd_in_pipe = 0;
	return (executor);
}

void	executor(t_token *tokens)
{
	t_executor	*executor;

	executor = init_executor(tokens);
	if (executor->has_pipe)
		exec_pipe(executor, tokens);
	exec_redir(executor, tokens);
	while (tokens)
	{
		if (tokens == token_pipe)
		{
			switch_fd(executor, (t_pipe *)tokens->data);
			tokens = tokens->next;
			exec_pipe(executor, tokens);
			exec_redir(executor, tokens);
			continue ;
		}
		tokens = tokens->next;
	}
}
