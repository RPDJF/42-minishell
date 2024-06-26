/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:27:04 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/12 17:12:56 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../env/env.h"

void	free_tword(t_word *cmd)
{
	t_word	*tmp;

	tmp = NULL;
	while (cmd)
	{
		if (cmd->str)
			gfree(cmd->str);
		tmp = cmd;
		cmd = cmd->next;
		gfree(tmp);
	}
}

char	*tw_strchr(t_word *cmd, int c)
{
	t_word	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strchr(tmp->str, c) != NULL)
			return (ft_strchr(tmp->str, c));
		else
			tmp = tmp->next;
	}
	return (NULL);
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
		if (tw_is_delem(tmp->cmd) == 1
			|| !tk_delem_syntax(tmp->cmd, false))
			break ;
		else if (tw_is_delem(tmp->cmd) == 2)
		{
			if (tmp)
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	*exit_tk(char **context, char *msg, int exitcode)
{
	error_msg(context, msg);
	update_exitcode(exitcode);
	return (NULL);
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
