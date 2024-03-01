/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:28:45 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 17:29:54 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	secure_exit(void)
{
	exit(0);
}

void	crash_exit(void)
{
	perror(strerror(errno));
	exit (1);
}
