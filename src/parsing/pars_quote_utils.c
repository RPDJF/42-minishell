#include "parsing.h"

bool	prev_quoted(t_word	*cmd)
{
	t_word	*tmp;

	tmp = cmd;
	if (!cmd)
		return (false);
	while (tmp)
	{
		if (tmp->is_quoted)
			return (true);
		tmp = tmp->prev;
	}
	return (false);
}

int	var_quoted(t_word *cmd)
{
	t_word	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '='))
		{
			if (tmp->is_quoted)
				return (0);
			else if (!tmp->is_quoted)
			{
				if (!prev_quoted(tmp->prev))
					return (1);
				else
					return (0);
			}
		}
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
