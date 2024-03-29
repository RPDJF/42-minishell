/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:46:49 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/29 20:35:57 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*get_prompt(t_minishell *minishell)
{
	char	*output;
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = getcwd(0, 0);
	home = 0;
	if (minishell->hostname && getenv("USER"))
		output = ft_strsjoin(10, C_MAGENTA, getenv("USER"), "@", \
						minishell->hostname, C_RESET, ":", C_CYAN, \
						getcwd(0, 0), C_RESET, "❥ ");
	else if (getenv("USER"))
		output = ft_strsjoin(6, C_MAGENTA, getenv("USER"),
				":", getcwd(0, 0), C_RESET, "❥ ");
	else
		output = ft_strsjoin(5, "minishell-", VERSION, ":", cwd, "❥ ");
	if (!output)
		crash_exit();
	home = getenv("HOME");
	if (home)
	{
		tmp = output;
		output = ft_strreplace(output, home, "~");
		free(tmp);
	}
	free(cwd);
	return (output);
}

char	*prompt(t_minishell *minishell)
{
	char	*input;
	char	*strprompt;

	while (true)
	{
		strprompt = get_prompt(minishell);
		if (!strprompt)
			return (0);
		input = 0;
		input = readline(strprompt);
		if (!input)
			continue ;
		if (*input && !ft_isspace(*input))
			add_history(input);
		gfree(strprompt);
		return (input);
	}
}
