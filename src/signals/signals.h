/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:42 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 20:41:09 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"
# include "../prompter/prompt.h"

//	init_signals:	Initializes the signals for the minishell
void	init_signals(void);
//	set_interactive:	Enables or disables the interactive mode
void	set_interactive(bool enable);
//	handle_sigint:	Handles the SIGINT signal
void	handle_sigint(void);
//	handle_sigquit:	Handles the SIGQUIT signal
void	handle_sigquit(void);

#endif