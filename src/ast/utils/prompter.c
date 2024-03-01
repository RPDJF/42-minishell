/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:11:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 19:20:48 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(t_minishell *minishell)
{
	char	*input;
	char	*strprompt;

	while (true)
	{
		if (minishell->hostname && getenv("USER"))
			strprompt = ft_strsjoin(10, PINK, getenv("USER"), "@",
					minishell->hostname, DEFAULT, ":", BLUE,
					getcwd(0, 0), DEFAULT, "❥ ");
		else if (getenv("USER"))
			strprompt = ft_strsjoin(8, PINK, getenv("USER"),
					DEFAULT, ":", BLUE, getcwd(0, 0), DEFAULT, "❥ ");
		else
			strprompt = ft_strsjoin(8, PINK, "minishell-0.1",
					DEFAULT, ":", BLUE, getcwd(0, 0), DEFAULT, "❥ ");
		if (!strprompt)
			return ;
		input = readline(strprompt);
		if (!input)
			exit(0);
		if (*input && !ft_isspace(*input))
		{
			printf("Added %s\n", input);
			add_history(input);
		}
		gfree(strprompt);
	}
}