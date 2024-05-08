/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:37:21 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 21:12:07 by rude-jes         ###   ########.fr       */
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
	if (get_minishell()->is_interactive)
	{
		get_minishell()->sigint = SIGINT;
		write(1, "\n", 1);
		if (!close_here_doc_fd())
			update_line();
		update_exitcode(130);
	}
	else
		write(1, "\n", 1);
}

void	handle_sigquit(void)
{
	if (get_minishell()->is_interactive)
		rl_redisplay();
	else
	{
		if (get_minishell()->cur_pid)
		{
			kill(get_minishell()->cur_pid, SIGQUIT);
			printf("Quit: %d\n", SIGQUIT);
		}
	}
}
