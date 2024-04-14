#include "executor.h"

//	execute_cmd: execute a command inside minishell
static void	execute_cmd(t_minishell *minishell, t_cmd *cmd)
{
	pid_t	*pid;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		execve(cmd->cmd, cmd->argv, minishell->envp(minishell));
		error_exit(0, "command not found", 127);
	}
	else if (cmd->pid < 0)
		crash_exit();
}

//	wait_tokens: wait for all tokens pid to finish executing
//	returns: the exit status of the last token
static int	wait_tokens(t_token *tokens)
{
	int	status;

	while (tokens)
	{
		if (tokens->type == token_cmd)
			waitpid(((t_cmd *)tokens->data)->pid, &status, 0);
		else if (tokens->type == token_builtin)
			waitpid(((t_builtin *)tokens->data)->pid, &status, 0);
		tokens = tokens->next;
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	return (status);
}

pid_t	fork_child(t_minishell *minishell, t_token *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->type == token_cmd)
		{
			execve(((t_cmd *)cmd->data)->cmd, ((t_cmd *)cmd->data)->argv,
				minishell->envp(minishell));
			error_exit(0, "command not found", 127);
		}
	}
	else if (pid < 0)
		crash_exit();
	return (pid);

}

void	executor(t_minishell *minishell, t_token *tokens)
{
	t_token	*token_head;

	token_head = tokens;
	while (tokens)
	{
		if (tokens->type == token_cmd)
			execute_cmd(minishell, (t_cmd *)tokens->data);
		tokens = tokens->next;
	}
	wait_tokens(token_head);
}
