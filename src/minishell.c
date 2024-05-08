/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:28:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 20:37:04 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env/env.h"
#include "prompter/prompt.h"
#include "signals/signals.h"

static char	*mini_gethostname(void)
{
	t_var	*hostname;

	hostname = get_var("NAME");
	if (!hostname)
		hostname = get_var("HOSTNAME");
	if (!hostname)
		return (0);
	return (ft_strdup(hostname->value));
}

static void	script_mode(void)
{
	t_minishell	*minishell;
	struct stat	buf;

	minishell = get_minishell();
	if (minishell->argc <= 1)
		return ;
	if (!stat(minishell->argv[1], &buf) && !S_ISDIR(buf.st_mode)
		&& !access(minishell->argv[1], R_OK))
	{
		dup2(open(minishell->argv[1], O_RDONLY), STDIN_FILENO);
		minishell->is_script = true;
	}
	else
		error_cmd(minishell->argv[1], true);
}

t_minishell	*init_minishell(int argc, char **argv, char **envp)
{
	static t_minishell	*minishell;

	if (minishell)
		return (minishell);
	else if (!argc || !argv)
		return (0);
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		crash_exit();
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->old_envp = envp;
	minishell->mini_envp = init_minienvp();
	minishell->envp = &var_to_tab;
	minishell->hostname = mini_gethostname();
	init_signals();
	script_mode();
	if (!minishell->is_script)
		ms_load_history();
	return (minishell);
}

t_minishell	*get_minishell(void)
{
	static t_minishell	*minishell;

	if (!minishell)
		minishell = init_minishell(0, 0, 0);
	return (minishell);
}
