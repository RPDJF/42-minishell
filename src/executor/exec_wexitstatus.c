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
	int	status;

	if (token->type == token_cmd)
	{
		if (((t_cmd *)token->data)->pid && !((t_cmd *)token->data)->status)
		{
			waitpid(((t_cmd *)token->data)->pid, &status, 0);
			((t_cmd *)token->data)->status = get_wexistatus(status);
			return (((t_cmd *)token->data)->status);
		}
		return (((t_cmd *)token->data)->status);
	}
	else if (token->type == token_subshell)
	{
		if (((t_subshell *)token->data)->pid
			&& !((t_subshell *)token->data)->status)
		{
			waitpid(((t_subshell *)token->data)->pid, &status, 0);
			((t_subshell *)token->data)->status = get_wexistatus(status);
			return (((t_subshell *)token->data)->status);
		}
		return (((t_subshell *)token->data)->status);
	}
	return (0);
}

int	wait_all_tokens(t_token *tokens)
{
	int	status;

	status = 0;
	while (tokens)
	{
		if (tokens->type == token_cmd || tokens->type == token_subshell
			|| tokens->type == token_var)
			status = wait_token(tokens);
		tokens = tokens->next;
	}
	return (status);
}
