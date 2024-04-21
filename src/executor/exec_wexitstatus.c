#include "executor.h"

static int	get_wexistatus(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	return (status);
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
