#include "../parsing/parsing.h"

void	free_all(t_token **token, t_tlex **lex, char **input)
{
	t_tlex	*tmp1;
	t_token	*tmp2;

	gfree(*input);
	while (*lex)
	{
		if ((*lex)->cmd)
			free_tword((*lex)->cmd);
		tmp1 = (*lex);
		*lex = (*lex)->next;
		gfree(tmp1);
	}
	while ((*token))
	{
		if ((*token)->type == token_stdin)
			free(((t_stdin *)(*token)->data)->limiter);
		else if ((*token)->type == token_var)
			free(((t_var_init *)(*token)->data)->name);
		free((*token)->data);
		tmp2 = *token;
		*token = (*token)->next;
		gfree(tmp2);
	}
}
