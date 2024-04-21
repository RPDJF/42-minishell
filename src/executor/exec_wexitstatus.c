#include "executor.h"

static int	get_wexistatus(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	return (status);
}

int	wait_last_token(t_executor *executor, t_token *tokens)
{
	t_token	*head;
	t_token	*last_pipe;
	t_cmd	*last_cmd;

	head = executor->tokens;
	while (head != tokens)
	{
		if (head->type == token_pipe)
			last_pipe = head;
		head = head->next;
	}
	while (last_pipe && last_pipe->type != token_cmd)
		last_pipe = last_pipe->next;
	if (!last_pipe)
		return (0);
	last_cmd = last_pipe->data;
	if (last_cmd->pid)
	{
		waitpid(last_cmd->pid, &last_cmd->status, 0);
		return (get_wexistatus(last_cmd->status));
	}
	return (last_cmd->status);
}

int	wait_tokens(t_executor *executor)
{
	t_token	*tokens;
	int		status;

	tokens = executor->tokens;
	status = 0;
	while (tokens)
	{
		if (tokens->type == token_cmd)
		{
			if (((t_cmd *)tokens->data)->pid)
			{
				waitpid(((t_cmd *)tokens->data)->pid, &status, 0);
				status = get_wexistatus(status);
			}
			else
				status = ((t_cmd *)tokens->data)->status;
		}
		tokens = tokens->next;
	}
	return (status);
}
