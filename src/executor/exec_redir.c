#include "executor.h"

static int	stdin_redir(t_context *context, t_stdin *stdin)
{
	int		fd;
	char	*filename;

	filename = 0;
	if (stdin->filename)
		filename = parse_words(stdin->filename);

	if (context->fd_in != STDIN_FILENO)
		close(context->fd_in);
	if (!stdin->is_heredoc)
	{
		fd = open(filename, O_RDONLY);
		context->fd_in = fd;
		context->fd_in_path = filename;
	}
	else
	{
		fd = here_doc(stdin->limiter);
		if (fd < 0)
			return (fd);
		context->fd_in = fd;
	}
	return (fd);
}

static int	stdout_redir(t_context *context, t_stdout *stdout)
{
	int		fd;
	char	*filename;

	filename = parse_words(stdout->filename);
	if (context->fd_out != STDOUT_FILENO)
		close(context->fd_out);
	if (stdout->is_append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	context->fd_out = fd;
	context->fd_out_path = filename;
	return (fd);
}

void	exec_redir(t_executor *executor, t_token *tokens)
{
	t_context	*context;

	context = executor->context;
	while (tokens && context)
	{
		if (tokens->type == token_stdin)
			context->fd_in = stdin_redir(context, (t_stdin *)tokens->data);
		else if (tokens->type == token_stdout)
			context->fd_out = stdout_redir(context, (t_stdout *)tokens->data);
		else if (tokens->type == token_pipe)
			context = context->next;
		tokens = tokens->next;
	}
}
