#include "parsing.h"

int	is_subshell(t_word *cmd)
{
	if (cmd->str[0] == '(' && !cmd->str[1]
		&& !cmd->is_quoted
		&& !cmd->next
		&& !cmd->prev)
		return (1);
	else if (cmd->str[0] == ')' && !cmd->str[1]
		&& !cmd->is_quoted
		&& !cmd->next
		&& !cmd->prev)
		return (2);
	return (0);
}

int	tk_subshell(t_token *subshl, t_pars *pars)
{
	t_token	*neww;

	subshl->data = ft_calloc(1, sizeof(t_subshell));
	subshl->type = token_subshell;
	pars->tmp1 = pars->tmp1->next;
	while (pars->tmp1)
	{
		if (is_subshell(pars->tmp1->cmd) == 2)
		{
			pars->tmp1 = pars->tmp1->next;
			break ;
		}
		else
		{
			neww = token_new(pars);
			if (!neww)
				return (0);
			token_add_back(&((t_subshell *)(subshl)->data)->token, neww);
		}
	}
	return (1);
}

void	*tk_type(t_token *token)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (token->type == token_cmd)
		str = ft_strjoin("syntax error near unexpected token ",
				join_tword(((t_cmd *)(token)->data)->cmd));
	else if (token->type == token_subshell)
		str = ft_strjoin("syntax error near unexpected token ",
				"subshell");
	else if (token->type == token_var)
	{
		str = ft_strjoin(\
			"syntax error near unexpected token ", "Variable initialization");
		gfree(tmp);
	}
	exit_tk((char *[]){APP_NAME, 0, 0}, str, 2);
	gfree(str);
	return (NULL);
}

void	*check_syntax_subshell(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == token_subshell)
		{
			while (token->next)
			{
				token = token->next;
				if (token && (token->type == token_cmd
						|| token->type == token_subshell
						|| token->type == token_var))
					return (tk_type(token));
				if (token && (token->type == token_pipe
						|| token->type == token_and || token->type == token_or))
					break ;
			}
		}
		if (token && token->next)
			token = token->next;
	}
	return (token);
}
