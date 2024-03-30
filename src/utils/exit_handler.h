/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:50:41 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/30 19:23:25 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_HANDLER_H
# define EXIT_HANDLER_H

# include "../../libs/betterft/betterft.h"

//	crash_exit: exit the program when unexpected error
void	crash_exit(void);
//	error_exit: exit the program when expected error with specific message
void	error_exit(char **context, char *msg, int exitcode);

#endif