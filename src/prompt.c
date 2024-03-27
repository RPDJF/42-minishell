/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:46:49 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/27 14:41:38 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(t_minishell *minishell)
{
	char	*output;

	if (minishell->hostname && getenv("USER"))
		output = ft_strsjoin(6, getenv("USER"), "@", \
						minishell->hostname, ":", getcwd(0, 0), "❥ ");
	else if (getenv("USER"))
		output = ft_strsjoin(4, getenv("USER"),
				":", getcwd(0, 0), "❥ ");
	else
		output = ft_strsjoin(5, "minishell-", VERSION, ":", getcwd(0, 0), "❥ ");
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
		input = readline(strprompt);
		if (!input)
			continue ;
		if (*input && !ft_isspace(*input))
			add_history(input);
		gfree(strprompt);
		return (input);
	}
}
