#include "../parsing/parsing.h"

void	free_all(t_token **token, t_tlex **lex)
{
	t_tlex	*tmp1;
	t_token	*tmp2;

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
			gfree(((t_stdin *)(*token)->data)->limiter);
		else if ((*token)->type == token_var)
			gfree(((t_var_init *)(*token)->data)->name);
		gfree((*token)->data);
		tmp2 = *token;
		*token = (*token)->next;
		gfree(tmp2);
	}
}
