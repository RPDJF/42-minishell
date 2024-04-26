#include "parsing.h"

int	token_syntax(t_token *token)
{
	if (token->type == token_pipe && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token '|'", 2);
		return (0);
	}
	if (token->type == token_or && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token '||'", 2);
		return (0);
	}
	if (token->type == token_and && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token '&&'", 2);
		return (0);
	}
	return (1);
}

char	*ft_rui(char *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (cmd[0] == '|' && cmd[1] == '|' && cmd[2] == '|')
		tmp = ft_strdup("`||'");
	else if (cmd[0] == '&' && !cmd[1])
		tmp = ft_strdup("`&'");
	else if (cmd[0] == '&' && cmd[1] == '&' && cmd[2] == '&')
		tmp = ft_strdup("`&&'");
	else if (cmd[0] == '<' && cmd[1] == '<' && cmd[2] == '<')
		tmp = ft_strdup("`<<'");
	else if (cmd[0] == '>' && cmd[1] == '>' && cmd[2] == '>')
		tmp = ft_strdup("`>>'");
	if (!tmp)
		crash_exit();
	return (tmp);
}

int	tk_delem_syntax(t_word *cmd, bool print)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (!cmd->is_quoted
		&& ((cmd->str[0] == '|' && cmd->str[1] == '|' && cmd->str[2] == '|')
			|| (cmd->str[0] == '&' && !cmd->str[1])
			|| (cmd->str[0] == '&' && cmd->str[1] == '&' && cmd->str[2] == '&')
			|| (cmd->str[0] == '<' && cmd->str[1] == '<' && cmd->str[2] == '<')
			|| (cmd->str[0] == '>'
				&& cmd->str[1] == '>' && cmd->str[2] == '>')))
	{
		if (print)
		{
			tmp = ft_rui(cmd->str);
			str = ft_strjoin("syntax error near unexpected token ", tmp);
			exit_tk((char *[]){APP_NAME, 0}, str, 2);
			gfree(str);
			gfree(tmp);
		}
		return (0);
	}
	return (1);
}
