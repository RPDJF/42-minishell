/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:06:10 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 11:48:28 by ilyanar          ###   ########.fr       */
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
	t_tlex		*lex;

	minishell = init_minishell(argc, argv, envp);
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
		lex = lexer(input);
		if (lex)
			for (t_tlex *tmp = lex; tmp; tmp = tmp->next)
				ft_printf("lexer: %s\n", tmp->cmd);
		parsing(&lex);
		gfree(input);
	}
	exit (0);
}
