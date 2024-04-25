#include "executor.h"

static int	get_wexistatus(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	return (status);
}

int	wait_token(t_token *token)
{
	t_cmd	*cmd;

	cmd = token->data;
	if (token->type == token_cmd)
	{
		if (cmd->pid)
		{
			waitpid(cmd->pid, &cmd->status, 0);
			cmd->status = get_wexistatus(cmd->status);
			return (cmd->status);
		}
		return (cmd->status);
	}
	return (0);
}

int	wait_all_tokens(t_executor *executor)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = executor->tokens;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			cmd = tokens->data;
			if (cmd->pid)
			{
				waitpid(cmd->pid, &cmd->status, 0);
				cmd->status = get_wexistatus(cmd->status);
			}
		}
		tokens = tokens->next;
	}
	return (cmd->status);
}
