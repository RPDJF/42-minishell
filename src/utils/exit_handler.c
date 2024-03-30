/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:58:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/30 19:22:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_handler.h"
#include "minishell.h"

void	crash_exit(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(1);
}

void	error_exit(char **context, char *msg, int exitcode)
{
	ft_putstr_fd(APP_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	while (context && *context)
	{
		ft_putstr_fd(*context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		context++;
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exitcode);
}
