/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:42 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/10 17:43:56 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	syntax_redirection(t_word *cmd, bool print)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (!cmd->is_quoted && !cmd->next)
	{
		if (!tk_delem_syntax(cmd, 1) || (tw_is_delem(cmd) > 0 && !print))
			return (0);
		if (tw_is_delem(cmd) > 0 && print)
		{
			tmp1 = ft_strjoin("syntax error near unexpected token `", \
				cmd->str);
			if (!tmp1)
				crash_exit();
			tmp2 = ft_strjoin(tmp1, "'");
			if (!tmp2)
				crash_exit();
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

int	syntax_at_end(t_token *token)
{
	while (token)
	{
		if ((token->type == token_or && !token->next)
			|| (token->type == token_and && !token->next)
			|| (token->type == token_pipe && !token->next))
		{
			if (token->type == token_or && !token->next)
				exit_tk((char *[]){APP_NAME, 0}, \
				"syntax error near unexpected token `||'", 2);
			else if (token->type == token_and && !token->next)
				exit_tk((char *[]){APP_NAME, 0}, \
				"syntax error near unexpected token `&&'", 2);
			else if (token->type == token_pipe && !token->next)
				exit_tk((char *[]){APP_NAME, 0}, \
				"syntax error near unexpected token `|'", 2);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
