#include "parsing.h"

int	prev_quoted(t_word	*cmd)
{
	t_word	*tmp;

	tmp = cmd;
	if (!cmd)
		return (1);
	while (tmp)
	{
		if (tmp->is_quoted == 1)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

int	var_quoted(t_word *cmd)
{
	t_word	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '=') != NULL)
		{
			if (tmp->is_quoted == 0 && prev_quoted(tmp->prev) == 1)
				return (1);
			else if (tmp->is_quoted == 1)
				return (0);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	tk_delem(t_token *neww, t_pars *pars)
{
	if (!pars->tmp1->cmd->is_quoted && !pars->tmp1->cmd->next)
	{
		if (pars->tmp1->cmd->str[0] == '|' && !pars->tmp1->cmd->str[1])
		{
			neww->type = token_pipe;
			neww->data = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
			if (!neww->data)
				crash_exit();
			pars->tmp1 = pars->tmp1->next;
			return (1);
		}
	}
	return (0);
}

int	tw_is_delem(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '|' && !cmd->str[1])
			|| (cmd->str[0] == '|' && cmd->str[1] == '|' && !cmd->str[2])
			|| (cmd->str[0] == '&' && cmd->str[1] == '&' && !cmd->str[2])))
		return (1);
	else if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '<' && !cmd->str[1])
			|| (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			|| (cmd->str[0] == '>' && !cmd->str[1])
			|| (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])))
		return (2);
	return (0);
}
