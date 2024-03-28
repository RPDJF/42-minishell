/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:18:04 by ruipa             #+#    #+#             */
/*   Updated: 2024/03/28 15:03:49 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(int argc, char **argv)
{
	bool	has_newline;
	int		i;

	(void)argc;
	has_newline = true;
	if (argv)
	{
		i = 0;
		while (++i, argv[i] && !ft_strcmp(argv[i], "-n"))
			has_newline = false;
		while (argv[i])
		{
			ft_putstr_fd(argv[i++], STDOUT_FILENO);
			if (argv[i])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (has_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exit (0);
}
