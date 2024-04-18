#include "executor.h"

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
			printf("waiting cmd pid: %d\n", ((t_cmd *)tokens->data)->pid);
			waitpid(((t_cmd *)tokens->data)->pid, &status, 0);
			status = get_wexistatus(status);
			printf("status: %d\n", status);
		}
		else if (tokens->type == token_builtin)
		{
			if (((t_builtin *)tokens->data)->pid)
			{
				printf("waiting builtin pid: %d\n", ((t_builtin *)tokens->data)->pid);
				waitpid(((t_builtin *)tokens->data)->pid, &status, 0);
				status = get_wexistatus(status);
				printf("status: %d\n", status);
			}
			else
				status = ((t_builtin *)tokens->data)->status;
		}
		tokens = tokens->next;
	}
	printf("FINAL status: %d\n", status);
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

static void	execute_token(t_executor *executor, t_token **tokens)
{
	if ((*tokens)->type == token_pipe)
	{
		switch_fd(executor, (t_pipe *)(*tokens)->data);
		(*tokens) = (*tokens)->next;
		exec_pipe(executor, (*tokens));
		exec_redir(executor, (*tokens));
		return ;
	}
	else if ((*tokens)->type == token_cmd || (*tokens)->type == token_builtin)
	{
		init_child(executor, (*tokens));
		if (executor->fd_in != STDIN_FILENO)
			close(executor->fd_in);
	}
	else if ((*tokens)->type == token_var)
		update_var((*tokens)->data);
	(*tokens) = (*tokens)->next;
}

void	executor(t_token *tokens)
{
	t_executor	*executor;

	executor = init_executor(tokens);
	if (executor->has_pipe)
		exec_pipe(executor, tokens);
	exec_redir(executor, tokens);
	while (tokens)
		execute_token(executor, &tokens);
	update_status_var(wait_tokens(executor));
	exit(0);
}
