#include "../lexer/lexer.h"
#include <stdio.h>
#include "parsing.h"

int	tk_is_var_init(t_token *neww, t_pars *pars)
{
	(void)neww;
	(void)pars;
	return (1);
}

t_token	*token_new(t_pars *pars)
{
	t_token	*neww;

	neww = ft_calloc(1, sizeof(t_token));
	if (!neww)
		crash_exit();
	if ((tw_strchr(pars->tmp1->cmd, '=') && !var_quoted(pars->tmp1->cmd)
			&& !tk_is_var_init(neww, pars)))
		return (NULL);
	else if (tw_is_delem(pars->tmp1->cmd) > 0)
	{
		if (!tk_delem(neww, pars))
			return (NULL);
	}
	else if (!tk_cmd(neww, pars))
		return (NULL);
	return (neww);
}

t_token	*parsing(t_tlex **lex)
{
	t_token	*token;
	t_token	*neww;
	t_pars	pars;

	token = NULL;
	ft_bzero(&pars, sizeof(t_pars));
	pars.tmp1 = *lex;
	while (pars.tmp1)
	{
		neww = token_new(&pars);
		if (!neww)
			return (free_exit_token(&token, lex));
		token_add_back(&token, neww);
	}
	return (token);
}
