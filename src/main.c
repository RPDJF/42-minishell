/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:06:10 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/31 20:12:32 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "parsing.h"
#include "lexeur.h"
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
		lex = lexeur(minishell, input);
		parsing(minishell, lex);
		ft_free_tab(lex);
		free(input);
	}
	exit (0);
}
