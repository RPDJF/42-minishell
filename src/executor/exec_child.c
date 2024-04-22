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
		argv = parse_words_arr(cmd->argv);
		path = parse_words(cmd->cmd);
		path = find_binary(path);
		if (!strchr(path, '/'))
			error_cmd(path, false);
		rl_clear_history();
		context = context->next;
		if (context)
			if (context->fd_in != STDIN_FILENO)
				close(context->fd_in);
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

static bool	is_builtin(t_cmd *cmd)
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

pid_t	init_child(t_context *context, t_token *tokens)
{
	pid_t	*pid;
	t_cmd	*cmd;

	pid = 0;
	cmd = (t_cmd *)tokens->data;
	if (is_builtin(cmd))
	{
		pid = &cmd->pid;
		builtin_child(context, cmd);
		update_var(new_var("_",
				parse_words(cmd->argv[cmd->argc - 1]), true, false));
	}
	else
	{
		cmd = (t_cmd *)tokens->data;
		pid = &cmd->pid;
		cmd_child(context, cmd);
		update_var(new_var("_",
				parse_words(cmd->argv[cmd->argc - 1]), true, false));
	}
	if (*pid < 0)
		crash_exit();
	return (*pid);
}
