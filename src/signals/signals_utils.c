/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:37:21 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/09 15:28:50 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static int	close_here_doc_fd(void)
{
	int	status;

	status = 0;
	if (get_minishell()->dup_stdin != STDIN_FILENO)
	{
		close(get_minishell()->dup_stdin);
		get_minishell()->dup_stdin = STDIN_FILENO;
		status = 1;
	}
	if (get_minishell()->here_doc_fd[1])
	{
		close(get_minishell()->here_doc_fd[1]);
		get_minishell()->here_doc_fd[1] = 0;
		status = 1;
	}
	if (get_minishell()->here_doc_fd[0])
	{
		close(get_minishell()->here_doc_fd[0]);
		get_minishell()->here_doc_fd[0] = 0;
		status = 1;
	}
	return (status);
}

static void	update_line(void)
{
	static size_t	userinfo_len;

	rl_on_new_line();
	rl_replace_line("", 0);
	if (!userinfo_len)
		userinfo_len = ft_strlen(get_userinfo());
	write(STDOUT_FILENO, get_userinfo(), userinfo_len);
	rl_redisplay();
}

void	handle_sigint(void)
{
	if (!get_minishell()->is_interactive)
		get_minishell()->sigint = SIGINT;
	if (isatty(STDIN_FILENO) && get_minishell()->is_interactive)
	{
		get_minishell()->sigint = SIGINT;
		write(1, "\n", 1);
		if (!close_here_doc_fd())
			update_line();
		update_exitcode(130);
	}
}

void	handle_sigquit(void)
{
	bool	is_interactive;

	is_interactive = get_minishell()->is_interactive;
	if (!is_interactive)
		get_minishell()->sigint = SIGQUIT;
	if (isatty(STDIN_FILENO) && is_interactive)
		rl_redisplay();
}
