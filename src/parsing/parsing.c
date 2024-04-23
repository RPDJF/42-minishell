#include "../lexer/lexer.h"
#include <stdio.h>
#include "parsing.h"

int	prev_quoted(t_word	*cmd)
{
	t_word	*tmp;

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
		if (ft_strchr(tmp->str, '=') != NULL)
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

int	do_tk_is_var_init(t_token *new, t_pars *pars)
{
	(void)new;
	(void)pars;
	return (1);
}

void	token_add_back(t_token **token, t_token *neww)
{
	t_token	*tmp;

	if (!token || !neww)
		return ;
	if (!*token)
		*token = neww;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
		neww->prev = tmp;
	}
}

int	tw_is_delem(t_word *cmd)
{
	if (cmd->is_quoted == 0 && !cmd->next && \
		(cmd->str[0] == '|' && !cmd->str[1]
			|| cmd->str[0] == '|' && cmd->str[1] == '|' && !cmd->str[2]
			|| cmd->str[0] == '&' && cmd->str[1] == '&' && !cmd->str[2]))
		return (1);
	else if (cmd->is_quoted == 0 && !cmd->next && \
			(cmd->str[0] == '<' && !cmd->str[1]
			|| cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2]
			|| cmd->str[0] == '>' && !cmd->str[1]
			|| cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2]))
		return (2);
	return (0);
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
			return (i);
		else if (tw_is_delem(tmp->cmd) == 2)
		{
			if (tmp->next)
				tmp = tmp->next;
			if (tmp->next)
				tmp = tmp->next;
			continue ;
		}
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	tk_cmd(t_token *new, t_pars *pars)
{
	t_cmd	*data_tmp;

	new->data = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new->data)
		crash_exit();
	data_tmp = new->data;
	data_tmp->cmd = pars->tmp1->cmd;
	data_tmp->argv = ft_calloc(arg_count(pars->tmp1->next) + 2, sizeof(t_word));
	if (!data_tmp->argv)
		crash_exit();
	data_tmp->argv[0] = pars->tmp1->cmd;
	return (1);
}

t_token	*token_new(t_tlex *lex, t_pars *pars)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		crash_exit();
	if ((tw_strchr(pars->tmp1->cmd, '=') && var_quoted(pars->tmp1->cmd)
			&& !do_tk_is_var_init(new, pars)))
		return (NULL);
	else if (!tk_cmd(new, pars))
		return (NULL);
	return (new);
}

t_token	*parsing(t_tlex **lex)
{
	t_token	*token;
	t_token	*new;
	t_pars	pars;

	ft_bzero(&pars, sizeof(t_pars));
	pars.tmp1 = *lex;
	while (pars.tmp1)
	{
		new = token_new(*lex, &pars);
		if (!new)
			return (free_exit_token(&token, lex));
		token_add_back(&token, new);
	}
	return (token);
}
