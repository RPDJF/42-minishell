#include "executor.h"

int	dup_fd(t_context *context)
{
	if (context->fd_in != STDIN_FILENO && context->fd_in >= 0)
	{
		dup2(context->fd_in, STDIN_FILENO);
		close(context->fd_in);
	}
	if (context->fd_out != STDOUT_FILENO && context->fd_out >= 0)
	{
		dup2(context->fd_out, STDOUT_FILENO);
		close(context->fd_out);
	}
	if (context->fd_in < 0)
	{
		error_msg((char *[]){APP_NAME,
			context->fd_in_path, 0}, strerror(errno));
		return (-1);
	}
	if (context->fd_out < 0)
	{
		error_msg((char *[]){APP_NAME,
			context->fd_out_path, 0}, strerror(errno));
		return (-1);
	}
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
	t_context	*context;

	context = executor->context;
	while (tokens)
	{
		if (tokens->type == token_pipe)
		{
			if (pipe(((t_pipe *)tokens->data)->pipe))
				crash_exit();
			if (context->fd_out != STDOUT_FILENO)
				close(context->fd_out);
			context->fd_out = ((t_pipe *)tokens->data)->pipe[1];
			context = context->next;
			if (context->fd_in != STDIN_FILENO)
				close(context->fd_in);
			context->fd_in = ((t_pipe *)tokens->data)->pipe[0];
		}
		tokens = tokens->next;
	}
	return (0);
}
