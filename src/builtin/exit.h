/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:26 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "../minishell.h"
# include "../env/env.h"
# include <readline/readline.h>

//	exit_ms: builtin exit command
int	exit_ms(int argc, char **argv);

#endif