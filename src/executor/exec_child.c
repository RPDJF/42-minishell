#include "executor.h"

static pid_t	cmd_child(t_executor *executor, t_cmd *cmd)
{
	char	*path;
	char	**argv;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (executor->fd_in_pipe)
			close(executor->fd_in_pipe);
		if (dup_fd(executor))
			exit(1);
		argv = parse_words_arr(cmd->argv);
		path = parse_words(cmd->cmd);
		path = find_binary(path);
		execve(path, argv, get_minishell()->envp());
		error_cmd(path);
		gfree(path);
		ft_free_tab(argv);
	}
	return (cmd->pid);
}

static int	start_builtin(t_executor *executor, t_cmd *builtin)
{
	int		status;
	char	*cmd;
	char	**argv;

	status = 127;
	cmd = parse_words(builtin->cmd);
	argv = parse_words_arr(builtin->argv);
	if (!ft_strcmp(cmd, "cd"))
		status = cd(builtin->argc, argv);
	else if (!ft_strcmp(cmd, "echo"))
		status = echo(builtin->argc, argv);
	else if (!ft_strcmp(cmd, "export"))
		status = export_ms(builtin->argc, argv);
	else if (!ft_strcmp(cmd, "exit"))
	{
		if (!executor->has_pipe)
			printf("exit\n");
		status = exit_ms(builtin->argc, argv);
	}
	else if (!ft_strcmp(cmd, "pwd"))
		status = pwd(builtin->argc, argv);
	gfree(cmd);
	ft_free_tab(argv);
	return (status);
}

static pid_t	builtin_child(t_executor *executor, t_cmd *builtin)
{
	int		fd_status;

	builtin->pid = 0;
	fd_status = dup_fd(executor);
	if (executor->has_pipe)
	{
		builtin->pid = fork();
		if (builtin->pid == 0)
		{
			if (executor->fd_in_pipe)
				close(executor->fd_in_pipe);
			if (fd_status)
				exit(1);
			builtin->status = start_builtin(executor, builtin);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			exit(builtin->status);
		}
	}
	if (!builtin->pid && !fd_status)
		builtin->status = start_builtin(executor, builtin);
	dup2(executor->original_fd_in, STDIN_FILENO);
	dup2(executor->original_fd_out, STDOUT_FILENO);
	return (builtin->pid);
}

static bool	is_builtin(t_cmd *cmd)
{
	bool	output;
	char	*cmd_str;

	cmd_str = parse_words(cmd->cmd);
	if (!ft_strcmp(cmd_str, "cd") || !ft_strcmp(cmd_str, "echo")
		|| !ft_strcmp(cmd_str, "export") || !ft_strcmp(cmd_str, "exit")
		|| !ft_strcmp(cmd_str, "pwd"))
		output = true;
	else
		output = false;
	gfree(cmd_str);
	return (output);
}

pid_t	init_child(t_executor *executor, t_token *tokens)
{
	pid_t	*pid;
	t_cmd	*cmd;

	pid = 0;
	cmd = (t_cmd *)tokens->data;
	if (is_builtin(cmd))
	{
		pid = &cmd->pid;
		builtin_child(executor, cmd);
		update_var(new_var("_",
				parse_words(cmd->argv[cmd->argc - 1]), true, false));
	}
	else
	{
		cmd = (t_cmd *)tokens->data;
		pid = &cmd->pid;
		cmd_child(executor, cmd);
		update_var(new_var("_",
				parse_words(cmd->argv[cmd->argc - 1]), true, false));
	}
	if (*pid < 0)
		crash_exit();
	return (*pid);
}
