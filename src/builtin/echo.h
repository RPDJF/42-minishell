/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:14 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:15 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "../minishell.h"

# define ECHO_OPTIONS "n"

typedef struct s_echo
{
	bool	has_newline;
	int		argc;
	char	**argv;
	void	(*exec)(char *str, int fd);
}	t_echo;

//	echo: builtin echo command
int	echo(int argc, char **argv);

#endif