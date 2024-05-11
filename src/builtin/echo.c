/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:24:55 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static t_echo	*init_echo(int argc, char **argv)
{
	t_echo	*echo;

	echo = galloc(sizeof(t_echo));
	echo->has_newline = true;
	echo->argc = argc;
	echo->argv = argv;
	echo->exec = &ft_putstr_fd;
	return (echo);
}

static bool	is_opt(char *str)
{
	bool	is_option_valid;
	int		i;

	if (*str != '-')
		return (false);
	while (++str, *str)
	{
		is_option_valid = false;
		i = -1;
		while (ECHO_OPTIONS[++i])
			if (*str == ECHO_OPTIONS[i])
				is_option_valid = true;
		if (!is_option_valid)
			return (false);
	}
	return (true);
}

static void	load_opt(t_echo *echo, char *options)
{
	while (++options, *options)
	{
		if (*options == 'n')
			echo->has_newline = false;
	}
}

int	echo(int argc, char **argv)
{
	t_echo	*echo;
	int		i;

	echo = init_echo(argc, argv);
	i = 0;
	while (argv[++i])
	{
		if (i == 1 && is_opt(argv[i]))
			load_opt(echo, argv[i]);
		else
		{
			echo->exec(argv[i], STDOUT_FILENO);
			if (argv[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
	}
	if (echo->has_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	gfree(echo);
	return (0);
}
