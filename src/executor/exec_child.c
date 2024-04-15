#include "executor.h"

// Test needed

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
		crash_exit();
	}
	return (pid);
}

pid_t	init_child(t_executor *executor, t_token *tokens)
{
	pid_t	pid;

	pid = 0;
	if (tokens->type == token_cmd)
	{
		pid = cmd_child(executor, (t_cmd *)tokens->data);
	}
}
