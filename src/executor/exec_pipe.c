#include "executor.h"

static int	init_pipe(t_executor *executor, t_pipe *pipes)
{
	if (pipe(pipes->pipe) < 0)
		crash_exit();
	executor->fd_out = pipes->pipe[1];
	executor->fd_in_pipe = pipes->pipe[0];
	return (0);
}

int	dup_fd(t_executor *executor)
{
	if (executor->fd_in != STDIN_FILENO && executor->fd_in >= 0)
	{
		dup2(executor->fd_in, STDIN_FILENO);
		close(executor->fd_in);
	}
	if (executor->fd_out != STDOUT_FILENO && executor->fd_out >= 0)
	{
		dup2(executor->fd_out, STDOUT_FILENO);
		close(executor->fd_out);
	}
	if (executor->fd_in < 0)
	{
		error_msg((char *[]){APP_NAME,
			executor->fd_in_path, 0}, strerror(errno));
		return (-1);
	}
	if (executor->fd_out < 0)
	{
		error_msg((char *[]){APP_NAME,
			executor->fd_out_path, 0}, strerror(errno));
		return (-1);
	}
	return (0);
}

void	switch_fd(t_executor *executor, t_pipe *pipe)
{
	if (executor->fd_in_pipe)
	{
		if (executor->fd_in != STDIN_FILENO)
			close(executor->fd_in);
		executor->fd_in = executor->fd_in_pipe;
		executor->fd_in_pipe = 0;
		close(pipe->pipe[1]);
	}
	else
		executor->fd_in = STDIN_FILENO;
	executor->fd_out = STDOUT_FILENO;
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
