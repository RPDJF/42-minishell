#include "executor.h"

static void	stdin_redir(t_context *context, t_stdin *stdin)
{
	int		fd;
	char	*filename;

	if (!stdin->filename)
		return ;
	filename = parse_words(stdin->filename);
	if (context->fd_in != STDIN_FILENO)
		close(context->fd_in);
	fd = open(filename, O_RDONLY);
	context->fd_in = fd;
	context->fd_in_path = filename;
}

static void	stdout_redir(t_context *context, t_stdout *stdout)
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
}

void	exec_redir(t_context *context, t_token *tokens)
{
	while (tokens && tokens->type != token_pipe
		&& tokens->type != token_and && tokens->type != token_or)
	{
		if (tokens->type == token_stdin
			&& context->fd_out >= 0 && context->fd_in >= 0)
			stdin_redir(context, (t_stdin *)tokens->data);
		else if (tokens->type == token_stdout
			&& context->fd_out >= 0 && context->fd_in >= 0)
			stdout_redir(context, (t_stdout *)tokens->data);
		tokens = tokens->next;
	}
}

void	exec_here_doc(t_context *context, t_token *tokens)
{
	if (tokens->type != token_stdin || !((t_stdin *)tokens->data)->is_heredoc)
		return ;
	context->fd_in = here_doc(((t_stdin *)tokens->data)->limiter,
			((t_stdin *)tokens->data)->is_quoted);
}
