/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:06:10 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/27 14:37:27 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_minishell	*minishell;
	char		*input;

	minishell = init_minishell();
	while (true)
	{
		input = prompt(minishell);
		if (!input)
			crash_exit();
	}
	exit (0);
}
