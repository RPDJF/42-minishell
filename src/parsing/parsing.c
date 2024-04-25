#include "parsing.h"
#include "../builtin/export.h"

t_word	*get_value_ofvar(char *str)
{
	t_word	*arg;

	arg = ft_calloc(1, sizeof(t_word));
	if (!arg)
		crash_exit();
	arg->str = ft_strdup(ft_strchr(str, '=') + 1);
	return (arg);
}

int	tk_is_var_init(t_token *neww, t_pars *pars)
{
	neww->data = (t_var_init *)ft_calloc(1, sizeof(t_var_init));
	if (!neww->data)
		crash_exit();
	neww->type = token_var;
	((t_var_init *)(neww)->data)->name = var_name(pars->tmp1->cmd->str);
	((t_var_init *)(neww)->data)->value = get_value_ofvar(pars->tmp1->cmd->str);
	((t_var_init *)(neww)->data)->value->next = pars->tmp1->cmd->next;
	pars->tmp1 = pars->tmp1->next;
	return (1);
}

t_token	*token_new_end(t_token *neww, t_pars *pars)
{
	if (tw_strchr(pars->tmp1->cmd, '=') && var_quoted(pars->tmp1->cmd))
	{
		if (!tk_is_var_init(neww, pars))
			return (NULL);
		return (neww);
	}
	else if (tw_is_delem(pars->tmp1->cmd) == 1)
	{
		if (!tk_delem(neww, pars))
			return (NULL);
		return (neww);
	}
	return (NULL);
}

t_token	*token_new(t_pars *pars)
{
	t_token	*neww;

	neww = NULL;
	if (tw_is_delem(pars->tmp1->cmd) == 2)
	{
		if (!token_add_back(&neww, newwtk_delem(pars->tmp1->cmd, pars)))
			return (NULL);
	}
	else
	{
		neww = ft_calloc(1, sizeof(t_token));
		if (!neww)
			crash_exit();
		if (!token_new_end(neww, pars))
		{
			if (!tk_cmd(neww, pars))
				return (NULL);
		}
	}
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
