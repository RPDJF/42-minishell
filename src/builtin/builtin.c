/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:23:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:23:50 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exec(char *builtin, int argc, char **argv, bool is_piped)
{
	if (!ft_strcmp(builtin, "cd"))
		return (cd(argc, argv));
	else if (!ft_strcmp(builtin, "echo"))
		return (echo(argc, argv));
	else if (!ft_strcmp(builtin, "env"))
		return (env(argc, argv));
	else if (!ft_strcmp(builtin, "exit"))
	{
		if (!is_piped)
			printf("exit\n");
		return (exit_ms(argc, argv));
	}
	else if (!ft_strcmp(builtin, "export"))
		return (export_ms(argc, argv));
	else if (!ft_strcmp(builtin, "pwd"))
		return (pwd(argc, argv));
	else if (!ft_strcmp(builtin, "unset"))
		return (unset(argc, argv));
	return (127);
}
