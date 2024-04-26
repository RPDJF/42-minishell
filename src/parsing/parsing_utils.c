#include "parsing.h"
#include "../env/env.h"

void	free_tword(t_word *cmd)
{
	t_word	*tmp1;
	t_word	*tmp2;

	tmp1 = cmd;
	while (tmp1)
	{
		if (tmp1->str)
			gfree(tmp1->str);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		gfree(tmp2);
	}
}

char	*tw_strchr(t_word *cmd, int c)
{
	t_word	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->str, c) != NULL)
			return (ft_strchr(tmp->str, c));
		else
			tmp = tmp->next;
	}
	return (NULL);
}

int	arg_count(t_tlex *arg)
{
	t_tlex	*tmp;
	int		i;

	i = 0;
	if (!arg)
		return (0);
	tmp = arg;
	while (tmp)
	{
		if (tw_is_delem(tmp->cmd) == 1)
			break ;
		else if (tw_is_delem(tmp->cmd) == 2)
		{
			if (tmp)
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	*exit_tk(char **context, char *msg, int exitcode)
{
	error_msg(context, msg);
	update_exitcode(exitcode);
	return (NULL);
}

char	*join_tword(t_word	*cmd)
{
	char	*filename;
	char	*tmp1;
	t_word	*tmp;

	tmp = cmd;
	filename = tmp->str;
	tmp = tmp->next;
	while (tmp)
	{
		tmp1 = ft_strjoin(filename, tmp->str);
		gfree(filename);
		tmp = tmp->next;
		if (!tmp)
		{
			filename = tmp1;
			break ;
		}
		filename = ft_strjoin(tmp1, tmp->str);
		gfree(tmp1);
		tmp = tmp->next;
	}
	return (filename);
}
