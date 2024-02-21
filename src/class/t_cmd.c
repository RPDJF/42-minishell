/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:43 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/21 17:27:54 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(int id, char *content, char **args)
{
	t_cmd	*cmd;

	cmd = galloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->id = id;
	cmd->content = content;
	cmd->args = args;
	// parse cmd
	return (cmd);
}
