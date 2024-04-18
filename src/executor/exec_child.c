#include "executor.h"
#include <sys/stat.h>

static void	error_cmd(char *path)
{
	int			err;
	struct stat	path_stat;

	err = errno;
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		error_exit((char *[]){APP_NAME, path, 0}, IS_DIR, 126);
	else if (err == EACCES)
		error_exit((char *[]){APP_NAME, path, 0}, strerror(err), 126);
	else if (!ft_strchr(path, '/'))
		error_exit((char *[]){path, 0}, COMMAND_NOT_FOUND, 127);
	else
		error_exit((char *[]){APP_NAME, path, 0}, strerror(err), 127);
}

static pid_t	cmd_child(t_executor *executor, t_cmd *cmd)
{
	int		err;
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
	}
	return (cmd->pid);
}

static int	start_builtin(t_executor *executor, t_builtin *builtin)
{
	int		status;
	char	**argv;

	status = 127;
	argv = parse_words_arr(builtin->argv);
	if (builtin->cmd == builtin_cd)
		status = cd(builtin->argc, argv);
	else if (builtin->cmd == builtin_echo)
		status = echo(builtin->argc, argv);
	else if (builtin->cmd == builtin_export)
		status = export_ms(builtin->argc, argv);
	else if (builtin->cmd == builtin_exit)
	{
		if (!executor->has_pipe)
			printf("exit\n");
		status = exit_ms(builtin->argc, argv);
	}
	else if (builtin->cmd == builtin_pwd)
		status = pwd(builtin->argc, argv);
	ft_free_tab(argv);
	return (status);
}

static pid_t	builtin_child(t_executor *executor, t_builtin *builtin)
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

pid_t	init_child(t_executor *executor, t_token *tokens)
{
	pid_t		*pid;
	t_cmd		*cmd;
	t_builtin	*builtin;

	pid = 0;
	if (tokens->type == token_cmd)
	{
		cmd = (t_cmd *)tokens->data;
		pid = &cmd->pid;
		cmd_child(executor, cmd);
		update_var(new_var("_",
				parse_words(cmd->argv[cmd->argc - 1]), true, false));
	}
	else if (tokens->type == token_builtin)
	{
		builtin = (t_builtin *)tokens->data;
		pid = &builtin->pid;
		builtin_child(executor, builtin);
		update_var(new_var("_",
				parse_words(builtin->argv[builtin->argc - 1]), true, false));
	}
	if (*pid < 0)
		crash_exit();
	return (*pid);
}
