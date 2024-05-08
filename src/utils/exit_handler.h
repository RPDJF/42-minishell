/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:59 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_HANDLER_H
# define EXIT_HANDLER_H

# include "../minishell.h"
# include "../utils/colors.h"
# include <readline/readline.h>

//	Error codes
//		Error messages
# define IS_DIR "Is a directory"
# define COMMAND_NOT_FOUND "command not found"

//	secure_exit: exits the program with a specific exit code freeing all memory
void	secure_exit(int exitcode);
//	crash_exit: exit the program when unexpected error
void	crash_exit(void);
//	error_exit: exit the program when expected error with specific message
void	error_exit(char **context, char *msg, int exitcode);
//	error_msg: sends specific error to the terminal without exiting
void	error_msg(char **context, char *msg);
//	error_cmd: sends specific error to the terminal and exits
void	error_cmd(char *path, bool is_script);

#endif