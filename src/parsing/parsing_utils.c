#include "parsing.h"

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
