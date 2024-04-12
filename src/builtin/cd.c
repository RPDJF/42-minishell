/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:22:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 01:39:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static t_cd	*init_cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = galloc(sizeof(t_cd));
	if (!cd)
		crash_exit();
	cd->argc = argc;
	cd->argv = argv;
	cd->exec = &chdir;
	return (cd);
}

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

int	cd(int argc, char **argv)
{
	t_cd	*cd;

	cd = init_cd(argc, argv);
	if (argc > 2)
		error_exit(get_context(argv), "too many arguments", 1);
	else if (argc < 2)
		return (cd->exec(getenv("HOME")));
	else
		return (cd->exec(argv[1]));
	gfree(cd);
}

int	main(int argc, char **argv)
{
	cd(argc, argv);
}
