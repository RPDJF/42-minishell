#include "../lexer/lexer.h"
#include <stdio.h>
#include "parsing.h"

void	*exit_tk(char **context, char *msg)
{
	error_msg(context, msg);
	return (NULL);
}

int	prev_quoted(t_word	*cmd)
{
	t_word	*tmp;

	tmp = cmd;
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

int	tk_is_var_init(t_token *new, t_pars *pars)
{
	(void)new;
	(void)pars;
	return (1);
}

t_token	**token_add_back(t_token **token, t_token *neww)
{
	t_token	*tmp;

	if (!token || !neww)
		return (NULL);
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
	return (token);
}

int	tw_is_delem(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '|' && !cmd->str[1])
			|| (cmd->str[0] == '|' && cmd->str[1] == '|' && !cmd->str[2])
			|| (cmd->str[0] == '&' && cmd->str[1] == '&' && !cmd->str[2])))
		return (1);
	else if (!cmd->is_quoted && !cmd->next
		&& ((cmd->str[0] == '<' && !cmd->str[1])
			|| (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			|| (cmd->str[0] == '>' && !cmd->str[1])
			|| (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])))
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
			break ;
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

t_token_type	define_type(t_word *cmd)
{
	if (!cmd->is_quoted && !cmd->next)
	{
		if (cmd->str[0] == '<' && !cmd->str[1])
			return (token_stdin);
		if (cmd->str[0] == '<' && cmd->str[1] == '<' && !cmd->str[2])
			return (token_stdin);
		if (cmd->str[0] == '>' && !cmd->str[1])
			return (token_stdout);
		if (cmd->str[0] == '>' && cmd->str[1] == '>' && !cmd->str[2])
			return (token_stdout);
	}
	return (0);
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

t_token	*newtk_delem(t_word *cmd, t_pars *pars)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		crash_exit();
	new->type = define_type(cmd);
	if (new->type == token_stdin && cmd->str[0] == '<'
		&& cmd->str[1] == '<' && !cmd->str[1])
	{
		if (!pars->tmp1->next)
			return (exit_tk((char *[]){APP_NAME, "token", 0}, \
					"syntax error near unexpected token `newline'"));
		new->data = (t_stdin *)ft_calloc(1, sizeof(t_stdin));
		if (!new->data)
			crash_exit();
		((t_stdin *)(new)->data)->limiter = join_tword(pars->tmp1->next->cmd);
		((t_stdin *)(new)->data)->is_heredoc = true;
	}
	if (new->type == token_stdin && cmd->str[0] == '<'
		&& !cmd->str[1])
	{
		if (!pars->tmp1->next)
			return (NULL);
		((t_stdin *)(new)->data)->filename = cmd->next;
	}
	return (new);
}

int	pars_arg_tk_cmd(t_token *new, t_cmd *token, t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->tmp1)
	{
		if (tw_is_delem(pars->tmp1->cmd) == 1)
			break ;
		else if ((tw_is_delem(pars->tmp1->cmd) == 2)
			&& (!(token_add_back(&new, newtk_delem(pars->tmp1->cmd, pars)))))
			return (0);
		else
		{
			token->argv[i] = pars->tmp1->cmd;
			i++;
			pars->tmp1 = pars->tmp1->next;
		}
	}
	token->argc = i;
	return (1);
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
	pars->tmp1 = pars->tmp1->next;
	if (!pars_arg_tk_cmd(new, data_tmp, pars))
		return (0);
	return (1);
}

int	tk_delem(t_token *new, t_pars *pars)
{
	if (!pars->tmp1->cmd->is_quoted && !pars->tmp1->cmd->next)
	{
		if (pars->tmp1->cmd->str[0] == '|' && !pars->tmp1->cmd->str[1])
		{
			new->type = token_pipe;
			new->data = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
			pars->tmp1 = pars->tmp1->next;
			return (1);
		}
	}
	return (0);
}

t_token	*token_new(t_pars *pars)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		crash_exit();
	if ((tw_strchr(pars->tmp1->cmd, '=') && !var_quoted(pars->tmp1->cmd)
			&& !tk_is_var_init(new, pars)))
		return (NULL);
	else if (tw_is_delem(pars->tmp1->cmd) == 1)
	{
		if (!tk_delem(new, pars))
			return (NULL);
	}
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
		new = token_new(&pars);
		if (!new)
			return (free_exit_token(&token, lex));
		token_add_back(&token, new);
	}
	return (token);
}
