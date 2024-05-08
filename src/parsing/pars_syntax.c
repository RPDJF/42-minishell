/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:42 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 16:26:42 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	syntax_redirection(t_word *cmd)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (!cmd->is_quoted && !cmd->next)
	{
		if (!tk_delem_syntax(cmd, 1))
			return (0);
		if (tw_is_delem(cmd) > 0)
		{
			tmp1 = ft_strjoin("syntax error near unexpected token `", cmd->str);
			tmp2 = ft_strjoin(tmp1, "'");
			gfree(tmp1);
			exit_tk((char *[]){APP_NAME, 0}, tmp2, 2);
			gfree(tmp2);
			return (0);
		}
	}
	return (1);
}

int	token_syntax(t_token *token)
{
	if (token->type == token_pipe && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token `|'", 2);
		return (0);
	}
	if (token->type == token_or && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token `||'", 2);
		return (0);
	}
	if (token->type == token_and && !token->prev)
	{
		exit_tk((char *[]){APP_NAME, 0}, \
			"syntax error near unexpected token `&&'", 2);
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
