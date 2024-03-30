/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:58:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/30 01:10:35 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_handler.h"

void	crash_exit(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(1);
}