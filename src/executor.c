/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:10:40 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/30 19:30:50 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	execute_cmd(t_minishell *minishell, t_cmd *cmd)
{
	pid_t	*pid;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		execve(cmd->cmd, cmd->argv, minishell->envp);
		error_exit(0, "command not found", 127);
	}
	else if (cmd->pid < 0)
		crash_exit();
}

void	executor(t_minishell *minishell, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == token_cmd)
			execute_cmd(minishell, (t_cmd *)tokens->data);
		tokens = tokens->next;
	}
}