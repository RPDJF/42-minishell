/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:22:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/28 17:15:06 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_context(char **argv)
{
	static char	**context;

	if (context)
		return (context);
	context = galloc(sizeof(char *) * 2);
	if (!context)
		crash_exit();
	context[0] = argv[0];
	context[1] = 0;
	return (context);
}

static int	case_handler(char *case)
{
	if (ft_strcmp(case, "~"))
}

int	cd(int argc, char **argv)
{
	if (argc > 2)
		error_exit(get_context(argv), "too many arguments", 1);
	else if (argc < 2)
		ft_printf("%s\n", getenv("USER"));
	else
		if (chdir(argv[1]))
			error_exit(get_context(argv), strerror(errno), 1);
	exit (0);
}

int	main(int argc, char **argv)
{
	cd(argc, argv);
}
