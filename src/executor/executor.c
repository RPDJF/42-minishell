#include "executor.h"

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
	int		status;

	tokens = executor->tokens;
	status = 0;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			waitpid(((t_cmd *)tokens->data)->pid, &status, 0);
			status = get_wexistatus(status);
		}
		else if (tokens->type == token_builtin)
		{
			if (((t_builtin *)tokens->data)->pid)
			{
				waitpid(((t_builtin *)tokens->data)->pid, &status, 0);
				status = get_wexistatus(status);
			}
			else
				status = ((t_builtin *)tokens->data)->status;
		}
		tokens = tokens->next;
	}
	return (status);
}

static void	update_status_var(int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		crash_exit();
	update_var(new_var("?", status_str, false, false));
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
			init_child(executor, tokens);
			if (executor->fd_in != STDIN_FILENO)
				close(executor->fd_in);
		}
		else if (tokens->type == token_var)
			update_var(tokens->data);
		tokens = tokens->next;
	}
	update_status_var(wait_tokens(executor));
}
