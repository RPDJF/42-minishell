#include "lexer.h"
#include <unistd.h>

int	ft_isdelem(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| str[i] == '(' || str[i] == ')')
		return (1);
	if ((str[i] == '&' && str[i + 1] == '&') || \
		(str[i] == '|' && str[i + 1] == '|'))
		return (2);
	return (0);
}

int	impair_pair_char(char *str, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	if (count % 2 == 0)
		return (0);
	return (1);
}

int	exit_print(char *str)
{
	ft_putendl_fd(str, STDOUT_FILENO);
	return (1);
}

t_tlex	*free_exit_lexer(t_tlex **tlex)
{
	t_tlex	*tmp1;
	t_word	*tmp2;
	t_word	*tmp3;

	tmp1 = *tlex;
	while (tmp1)
	{
		tmp2 = tmp1->cmd;
		while (tmp2)
		{
			if (tmp2->str)
				free(tmp2->str);
			tmp3 = tmp2;
			tmp2 = tmp2->next;
			if (tmp3)
				free(tmp3);
		}
		tmp1 = tmp1->next;
	}
	return (NULL);
}
