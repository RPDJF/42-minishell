/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:33 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:33 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	is_builtin(t_cmd *cmd)
{
	bool	output;
	char	*cmd_str;

	cmd_str = parse_words(cmd->cmd);
	if (!ft_strcmp(cmd_str, "cd") || !ft_strcmp(cmd_str, "echo")
		|| !ft_strcmp(cmd_str, "export") || !ft_strcmp(cmd_str, "exit")
		|| !ft_strcmp(cmd_str, "pwd") || !ft_strcmp(cmd_str, "unset")
		|| !ft_strcmp(cmd_str, "env"))
		output = true;
	else
		output = false;
	gfree(cmd_str);
	return (output);
}

t_token	*find_last_cmd(t_executor *exec, t_token *token)
{
	t_token	*cmd;
	t_token	*p;

	cmd = 0;
	p = exec->tokens;
	while (p != token && p)
	{
		if (p->type == token_cmd
			&& (((t_cmd *)p->data)->pid
				|| ((t_cmd *)p->data)->status))
			cmd = p;
		if (p->type == token_subshell
			&& (((t_subshell *)p->data)->pid
				|| ((t_subshell *)p->data)->status))
			cmd = p;
		p = p->next;
	}
	return (cmd);
}

t_cmd	*find_cmd(t_cmd *cmd)
{
	char	*cmd_str;

	parse_cmd_var(cmd);
	cmd_str = parse_words(cmd->cmd);
	while (cmd->cmd && cmd->cmd->is_var && !*cmd_str)
	{
		cmd->argv++;
		cmd->argc--;
		cmd->cmd = *cmd->argv;
		gfree(cmd_str);
		if (cmd->cmd)
			cmd_str = parse_words(cmd->cmd);
		else
			cmd_str = 0;
	}
	gfree(cmd_str);
	if (!cmd->cmd)
		return (0);
	return (cmd);
}

void	close_all_fd(t_context *context)
{
	t_context	*prev;

	close(*context->og_fd_in);
	close(*context->og_fd_out);
	prev = context->prev;
	while (context)
	{
		if (context->fd_in != STDIN_FILENO && context->fd_in >= 0)
			close(context->fd_in);
		if (context->fd_out != STDOUT_FILENO && context->fd_out >= 0)
			close(context->fd_out);
		context = context->next;
	}
	while (prev)
	{
		if (prev->fd_in != STDIN_FILENO && prev->fd_in >= 0)
			close(prev->fd_in);
		if (prev->fd_out != STDOUT_FILENO && prev->fd_out >= 0)
			close(prev->fd_out);
		prev = prev->prev;
	}
}
