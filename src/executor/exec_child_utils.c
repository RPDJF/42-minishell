/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:13 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:28:00 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	fill_cmd_argv(t_cmd *cmd, t_word **argv, char **cmd_split)
{
	size_t	i;

	i = 0;
	while (cmd_split[i])
	{
		argv[i] = ft_calloc(1, sizeof(t_word));
		argv[i]->str = cmd_split[i];
		i++;
	}
	gfree(cmd_split);
	ft_memmove(argv + i,
		cmd->argv + 1, words_arr_len(cmd->argv) * sizeof(t_word *));
	gfree(cmd->argv);
	return (i);
}

t_word	**parse_cmd_var(t_cmd *cmd)
{
	t_word	**argv;
	char	*cmd_str;
	char	**cmd_split;

	cmd_str = ft_strtrim(cmd->cmd->str, " \t");
	if (!*cmd_str || *cmd_str != '$')
		return (cmd->argv);
	cmd_str = parse_words(cmd->cmd);
	cmd_split = ft_split(cmd_str, ' ');
	gfree(cmd_str);
	argv = galloc((ft_tablen(cmd_split)
				+ words_arr_len(cmd->argv)) * sizeof(t_word *));
	fill_cmd_argv(cmd, argv, cmd_split);
	cmd->argv = argv;
	cmd->cmd = argv[0];
	cmd->argc = words_arr_len(argv);
	return (argv);
}
