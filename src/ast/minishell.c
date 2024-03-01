/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:20:04 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 17:00:42 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_astnode *astnode)
{
	int	i;

	if (astnode->l_node)
	{
		print_ast(astnode->l_node);
		printf(" ");
	}
	i = 0;
	while (astnode->args[i])
	{
		printf("%s", astnode->args[i++]);
		if (astnode->args[i])
			printf(" ");
	}
	if (astnode->r_node)
	{
		printf(" ");
		print_ast(astnode->r_node);
	}
}

int	main(void)
{
	t_minishell	*minishell;
	t_astnode	*ast;

	ast = generate_fake_ast();
	print_ast(ast);
	printf("\n");
	minishell = minishell_init();
	start_prompt(minishell);
	exit (0);
}
