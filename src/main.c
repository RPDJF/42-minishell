/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:06:10 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/05 15:24:17 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "parsing.h"
#include "lexer.h"
#include "utils/exit_handler.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	char		*input;
	char		**lex;

	minishell = init_minishell(argc, argv, envp);
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
		lex = lexer(input);
		for (int d = 0; lex[d]; d++)
			ft_printf("lexer[%d]: %s\n", d, lex[d]);
		ft_free_tab(lex);
		parsing(lex);
		gfree(input);
	}
	exit (0);
}
