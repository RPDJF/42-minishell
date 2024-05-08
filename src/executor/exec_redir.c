/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:21 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 17:30:59 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	update_err_fd(t_context *context, char *msg, char *path)
{
	error_msg((char *[]){APP_NAME, path, 0}, msg);
	update_exitcode(1);
	context->err_fd = 0;
}

static void	stdin_redir(t_context *context, t_stdin *stdin)
{
	int		fd;
	char	*filename;

	if (!stdin->filename || stdin->is_heredoc)
		return ;
	filename = parse_words_line(stdin->filename);
	if (ft_strchr(filename, 28))
	{
		gfree(filename);
		context->fd_in_path = join_words(stdin->filename);
		update_err_fd(context, "ambiguous redirect", context->fd_in_path);
		context->fd_in = -1;
		return ;
	}
	fd = open(filename, O_RDONLY);
	context->fd_in = fd;
	context->fd_in_path = filename;
	if (context->fd_in < 0)
		update_err_fd(context, strerror(errno), context->fd_in_path);
}

static void	stdout_redir(t_context *context, t_stdout *stdout)
{
	int		fd;
	char	*filename;

	filename = parse_words_line(stdout->filename);
	if (ft_strchr(filename, 28))
	{
		gfree(filename);
		context->fd_out_path = join_words(stdout->filename);
		update_err_fd(context, "ambiguous redirect", context->fd_out_path);
		context->fd_out = -1;
		return ;
	}
	if (stdout->is_append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	context->fd_out = fd;
	context->fd_out_path = filename;
	if (context->fd_out < 0)
		update_err_fd(context, strerror(errno), context->fd_out_path);
}

void	exec_redir(t_context *context, t_token *tokens)
{
	while (tokens && tokens->type != token_pipe
		&& tokens->type != token_and && tokens->type != token_or)
	{
		if (tokens->type == token_stdin
			&& context->fd_out >= 0 && context->fd_in >= 0)
		{
			if (context->fd_in != STDIN_FILENO
				&& !((t_stdin *)tokens->data)->is_heredoc)
				close(context->fd_in);
			stdin_redir(context, (t_stdin *)tokens->data);
		}
		else if (tokens->type == token_stdout
			&& context->fd_out >= 0 && context->fd_in >= 0)
		{
			if (context->fd_out != STDOUT_FILENO)
				close(context->fd_out);
			stdout_redir(context, (t_stdout *)tokens->data);
		}
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
