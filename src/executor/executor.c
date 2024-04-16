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
	else
		executor->fd_in = STDIN_FILENO;
	executor->fd_out = STDOUT_FILENO;
}

static t_executor	*init_executor(t_token *tokens)
{
	t_executor	*executor;

	executor = galloc(sizeof(t_executor));
	if (!executor)
		crash_exit();
	executor->original_fd_in = dup(STDIN_FILENO);
	executor->original_fd_out = dup(STDOUT_FILENO);
	executor->has_pipe = has_pipe(tokens);
	executor->tokens = tokens;
	executor->fd_in = STDIN_FILENO;
	executor->fd_out = STDOUT_FILENO;
	executor->fd_in_pipe = 0;
	return (executor);
}

static int	wait_tokens(t_executor *executor)
{
	t_token	*tokens;
	int	status;

	tokens = executor->tokens;
	status = 0;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			ft_putendl_fd("waiting for cmd", STDERR_FILENO);
			waitpid(((t_cmd *)tokens->data)->pid, &status, 0);
			ft_putendl_fd("waited for cmd", STDERR_FILENO);
		}
		else if (tokens->type == token_builtin)
		{
			ft_putendl_fd("waiting for builtin", STDERR_FILENO);
			waitpid(((t_builtin *)tokens->data)->pid, &status, 0);
			ft_putendl_fd("waited for builtin", STDERR_FILENO);
		}
		tokens = tokens->next;
	}
	return (status);
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
		if (tokens->type == token_pipe)
		{
			switch_fd(executor, (t_pipe *)tokens->data);
			tokens = tokens->next;
			exec_pipe(executor, tokens);
			exec_redir(executor, tokens);
			continue ;
		}
		else if (tokens->type == token_cmd || tokens->type == token_builtin)
		{
			ft_putendl_fd("starting process", STDERR_FILENO);
			init_child(executor, tokens);
			ft_putendl_fd("started process", STDERR_FILENO);
		}
		tokens = tokens->next;
	}
	wait_tokens(executor);
}
