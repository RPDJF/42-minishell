/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:36:24 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 23:11:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "../minishell.h"

# define OPTIONS "n"

typedef struct s_echo
{
	bool	has_newline;
	int		argc;
	char	**argv;
	void	(*exec)(char *str, int fd);
}	t_echo;

#endif