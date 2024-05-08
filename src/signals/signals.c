/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:38 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 21:11:10 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
		handle_sigint();
	else if (signum == SIGQUIT)
		handle_sigquit();
}

void	set_interactive(bool enable)
{
	get_minishell()->is_interactive = enable;
	if (enable)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_handler);
}

void	init_signals(void)
{
	set_interactive(true);
	signal(SIGINT, signal_handler);
}
