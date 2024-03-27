/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:09 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/27 14:02:53 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/betterft/betterft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_minishell
{
	char		*hostname;
}				t_minishell;

//		init_minishell: init a new minishell instance
t_minishell	*init_minishell(void);
//		crash_exit: exit the program when unexpected error
void		crash_exit(void);

char		*prompt(t_minishell *minishell);
#endif