/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:23 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:24 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

static void	fn(char **context, char *errmsg, int exitcode)
{
	if (errmsg)
		error_exit(context, errmsg, exitcode % 256);
	else
		secure_exit(exitcode % 256);
}

int	exit_ms(int argc, char **argv)
{
	char	*cmp;
	int		exitcode;

	if (argc <= 2 && argv[1])
	{
		exitcode = ft_atoi(argv[1]);
		cmp = ft_itoa(exitcode);
		if (!cmp)
			crash_exit();
		if (argv[1][0] == '+')
			argv[1]++;
		if (!ft_strcmp(argv[1], cmp))
			fn(0, 0, exitcode);
		fn((char *[]){APP_NAME, "exit", argv[1], 0},
			"numeric argument required", 2);
	}
	if (argc > 2)
	{
		error_msg((char *[]){APP_NAME, "exit", 0}, "too many arguments");
		return (1);
	}
	else
		fn(0, 0, 0);
	return (0);
}
