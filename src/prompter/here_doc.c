/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:02 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:03 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static char	*expand_var(char *str, char *cursor)
{
	char	*var;
	char	*value;
	char	*output;
	size_t	len;

	len = varlen(cursor);
	var = ft_substr(str, cursor - str, len);
	if (!var)
		crash_exit();
	value = get_var_value(var + 1);
	if (!value)
		crash_exit();
	output = ft_strreplace_first(str, var, value);
	if (!output)
		crash_exit();
	gfree(var);
	return (output);
}

static char	*expand_str(char *str)
{
	char	*output;
	char	*cursor;
	char	*tmp;

	output = str;
	cursor = ft_strchr(output, '$');
	while (cursor && varlen(cursor) <= 1)
		cursor = ft_strchr(cursor + 1, '$');
	while (cursor)
	{
		tmp = output;
		output = expand_var(output, cursor);
		gfree(tmp);
		cursor = ft_strchr(output, '$');
		while (cursor && varlen(cursor) <= 1)
			cursor = ft_strchr(cursor + 1, '$');
	}
	return (output);
}

int	reset_heredoc(bool close_fd)
{
	if (close_fd && get_minishell()->here_doc_fd[0] != 0)
		close(get_minishell()->here_doc_fd[0]);
	if (close_fd && get_minishell()->here_doc_fd[1] != 0)
		close(get_minishell()->here_doc_fd[1]);
	get_minishell()->here_doc_fd[0] = 0;
	get_minishell()->here_doc_fd[1] = 0;
	if (get_minishell()->dup_stdin != STDIN_FILENO)
		close (get_minishell()->dup_stdin);
	get_minishell()->dup_stdin = STDIN_FILENO;
	return (-1);
}

static char	*prompt_here_doc(char *delimiter)
{
	char	*line;
	char	*msg;

	write (STDOUT_FILENO, "> ", 2);
	line = ft_get_next_line(get_minishell()->dup_stdin);
	if (!line && get_minishell()->sigint != SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		msg = ft_arrjoin((char *[])
			{"here-document delimited by end-of-file (wanted `",
				delimiter, "')", 0});
		if (!msg)
			crash_exit();
		error_msg((char *[]){APP_NAME, "warning", 0}, msg);
		gfree(msg);
		return (0);
	}
	if (line)
		line[ft_strlen(line) - 1] = 0;
	return (line);
}

int	here_doc(char *delimiter, bool is_quoted)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		crash_exit();
	get_minishell()->here_doc_fd[0] = pipe_fd[0];
	get_minishell()->here_doc_fd[1] = pipe_fd[1];
	get_minishell()->dup_stdin = dup(STDIN_FILENO);
	line = prompt_here_doc(delimiter);
	while (line && ft_strcmp(line, delimiter))
	{
		if (!is_quoted)
			line = expand_str(line);
		ft_putendl_fd(line, pipe_fd[1]);
		gfree(line);
		if (get_minishell()->sigint == SIGINT)
			return (reset_heredoc(true));
		line = prompt_here_doc(delimiter);
	}
	close(pipe_fd[1]);
	reset_heredoc(false);
	return (pipe_fd[0]);
}
