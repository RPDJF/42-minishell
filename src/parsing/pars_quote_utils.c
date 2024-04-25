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
		if (ft_strchr(tmp->str, '='))
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

bool	is_it_quoted(t_word *cmd)
{
	t_word	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->is_quoted)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
