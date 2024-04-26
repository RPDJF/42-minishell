#include "parsing.h"

int	is_subshell(t_word *cmd)
{
	if (cmd->str[0] == '(' && !cmd->str[1]
		&& !cmd->is_quoted
		&& !cmd->next
		&& !cmd->prev)
		return (1);
	else if (cmd->str[0] == ')' && !cmd->str[1]
		&& !cmd->is_quoted
		&& !cmd->next
		&& !cmd->prev)
		return (2);
	return (0);
}

int	tk_subshell(t_token *subshl, t_pars *pars)
{
	t_token	*neww;

	subshl->data = ft_calloc(1, sizeof(t_subshell));
	subshl->type = token_subshell;
	pars->tmp1 = pars->tmp1->next;
	while (pars->tmp1)
	{
		if (is_subshell(pars->tmp1->cmd) == 2)
		{
			pars->tmp1 = pars->tmp1->next;
			break ;
		}
		else
		{
			neww = token_new(pars);
			if (!neww)
				return (0);
			token_add_back(&((t_subshell *)(subshl)->data)->token, neww);
		}
	}
	return (1);
}
