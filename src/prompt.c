/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:46:49 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/29 22:41:17 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*parse_prompt(char *prompt)
{
	char	*home;
	char	*tmp;

	home = getenv("HOME");
	if (home)
	{
		tmp = prompt;
		prompt = ft_strreplace(prompt, home, "~");
		free(tmp);
	}
	return (prompt);
}

static char	*get_prompt(t_minishell *minishell)
{
	char	*output;
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		crash_exit();
	if (minishell->hostname && getenv("USER"))
		output = ft_strsjoin(10, C_MAGENTA, getenv("USER"), "@",
				minishell->hostname, C_RESET, ":", C_CYAN,
				cwd, C_RESET, ENDLINE);
	else if (getenv("USER"))
		output = ft_strsjoin(8, C_MAGENTA, getenv("USER"),
				C_RESET, ":", C_CYAN, cwd, C_RESET, ENDLINE);
	else
		output = ft_strsjoin(8, C_MAGENTA, "minishell-", C_CYAN, VERSION,
				C_RESET, ":", cwd, ENDLINE);
	if (!output)
		crash_exit();
	free(cwd);
	output = parse_prompt(output);
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
