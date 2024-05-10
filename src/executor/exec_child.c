/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:15 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 18:54:48 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static pid_t	cmd_child(t_context *context, t_cmd *cmd)
{
	char	*path;
	char	**argv;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (dup_fd(context))
			secure_exit(1);
		close_all_fd(context);
		argv = parse_words_arr(cmd->argv);
		path = argv[0];
		path = find_binary(path);
		if (!ft_strchr(path, '/'))
			error_cmd(path, false);
		rl_clear_history();
		while (context)
		{
			if (context->fd_in != STDIN_FILENO)
				close(context->fd_in);
			context = context->next;
		}
		execve(path, argv, get_minishell()->envp());
		error_cmd(path, false);
	}
	return (cmd->pid);
}

static int	start_builtin(t_context *context, t_cmd *builtin)
{
	char	*cmd;
	char	**argv;

	cmd = parse_words(builtin->cmd);
	argv = parse_words_arr(builtin->argv);
	builtin->status
		= builtin_exec(cmd, builtin->argc, argv, *context->has_pipe);
	gfree(cmd);
	ft_free_tab(argv);
	return (builtin->status);
}

static pid_t	builtin_child(t_context *context, t_cmd *builtin)
{
	int		fd_status;

	builtin->pid = 0;
	fd_status = dup_fd(context);
	if (*context->has_pipe)
	{
		builtin->pid = fork();
		if (builtin->pid == 0)
		{
			close_all_fd(context);
			if (fd_status)
				secure_exit(1);
			builtin->status = start_builtin(context, builtin);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			secure_exit(builtin->status);
		}
	}
	if (!builtin->pid && !fd_status)
		builtin->status = start_builtin(context, builtin);
	if (fd_status)
		builtin->status = 1;
	dup2(*context->og_fd_in, STDIN_FILENO);
	dup2(*context->og_fd_out, STDOUT_FILENO);
	return (builtin->pid);
}

static void	exec_child(t_cmd *cmd, t_token *tokens)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (is_builtin(cmd))
		minishell->cur_pid = builtin_child(tokens->context, cmd);
	else
		minishell->cur_pid = cmd_child(tokens->context, cmd);
	if (cmd->pid < 0)
		crash_exit();
	if (tokens->context->fd_in != STDIN_FILENO
		&& tokens->context->fd_in >= 0)
		close(tokens->context->fd_in);
	if (tokens->context->fd_out != STDOUT_FILENO
		&& tokens->context->fd_out >= 0)
		close(tokens->context->fd_out);
}

pid_t	init_child(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = find_cmd((t_cmd *)tokens->data);
	if (cmd)
		update_dash(parse_words(cmd->argv[cmd->argc - 1]));
	if (!cmd)
	{
		update_dash(parse_words(0));
		((t_cmd *)tokens->data)->pid = 0;
		return (0);
	}
	cmd = (t_cmd *)tokens->data;
	exec_child(cmd, tokens);
	return (cmd->pid);
}
