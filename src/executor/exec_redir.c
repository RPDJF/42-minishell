#include "executor.h"

static int	stdin_redir(t_executor *executor, t_stdin *stdin)
{
	int	fd;

	if (executor->fd_in != STDIN_FILENO)
		close(executor->fd_in);
	if (!stdin->is_heredoc)
	{
		fd = open(stdin->filename, O_RDONLY);
		executor->fd_in = fd;
		executor->fd_in_path = stdin->filename;
	}
	else
	{
		fd = here_doc(stdin->limiter);
		if (fd < 0)
			return (fd);
		executor->fd_in = fd;
	}
	return (fd);
}

static int	stdout_redir(t_executor *executor, t_stdout *stdout)
{
	int	fd;

	if (executor->fd_out != STDOUT_FILENO)
		close(executor->fd_out);
	if (stdout->is_append)
		fd = open(stdout->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(stdout->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	executor->fd_out = fd;
	executor->fd_out_path = stdout->filename;
	return (fd);
}

void	exec_redir(t_executor *executor, t_token *tokens)
{
	while (tokens && tokens->type != token_pipe)
	{
		if (tokens->type == token_stdin)
			executor->fd_in = stdin_redir(executor, (t_stdin *)tokens->data);
		else if (tokens->type == token_stdout)
			executor->fd_out = stdout_redir(executor, (t_stdout *)tokens->data);
		tokens = tokens->next;
	}
}
