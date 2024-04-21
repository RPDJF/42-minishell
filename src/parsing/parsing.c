#include "../lexer/lexer.h"
#include "parsing.h"

char	*tw_strchr(t_word *cmd, int c)
{
	t_word	*tmp;

	while (tmp)
	{
		if (ft_strchr(tmp->str, c) != NULL)
			return (ft_strchr(tmp->str, c));
		else
			tmp = tmp->next;
	}
	return (NULL);
}

t_token	*parsing(t_tlex *lex)
{
	t_token	*token;
	t_tlex	*tmp1;
	t_tlex	*tmp2;

	return (token);
}
