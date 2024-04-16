#include "executor.h"

static pid_t	cmd_child(t_executor *executor, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;
	char	**argv;

	pid = fork();
	if (pid == 0)
	{
		dup2(executor->fd_in, STDIN_FILENO);
		dup2(executor->fd_out, STDOUT_FILENO);
		argv = parse_words_arr(cmd->argv);
		path = parse_words(cmd->cmd);
		path = find_binary(path);
		execve(path, argv, get_minishell()->envp());
		error_exit((char *[]){path, 0}, "command not found", 127);
	}
	if (pid < 0)
		crash_exit();
	return (pid);
}

static int	start_builtin(t_builtin *builtin)
{
	int		status;
	char	**argv;

	argv = parse_words_arr(builtin->argv);
	if (builtin->cmd == builtin_cd)
		status = cd(builtin->argc, argv);
	else if (builtin->cmd == builtin_echo)
		status = echo(builtin->argc, argv);
	ft_free_tab(argv);
	return (status);
}

static pid_t	builtin_child(t_executor *executor, t_builtin *builtin)
{
	pid_t	pid;
	int		status;

	pid = 0;
	dup2(executor->fd_in, STDIN_FILENO);
	close(executor->fd_in);
	dup2(executor->fd_out, STDOUT_FILENO);
	close(executor->fd_out);
	if (executor->has_pipe)
	{
		pid = fork();
		if (pid == 0)
		{
			status = start_builtin(builtin);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			exit(status);
		}
		if (pid < 0)
			crash_exit();
		return (pid);
	}
	start_builtin(builtin);
	dup2(executor->original_fd_in, STDIN_FILENO);
	dup2(executor->original_fd_out, STDOUT_FILENO);
	return (pid);
}

pid_t	init_child(t_executor *executor, t_token *tokens)
{
	pid_t	*pid;

	if (tokens->type == token_cmd)
	{
		pid = &((t_cmd *)tokens->data)->pid;
		*pid = cmd_child(executor, (t_cmd *)tokens->data);
	}
	else if (tokens->type == token_builtin)
	{
		pid = &((t_builtin *)tokens->data)->pid;
		*pid = builtin_child(executor, (t_builtin *)tokens->data);
	}
	return (*pid);
}
