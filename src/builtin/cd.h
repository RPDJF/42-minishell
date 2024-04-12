/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:15:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 01:29:02 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../minishell.h"

typedef struct s_cd
{
	int		argc;
	char	**argv;
	int 	(*exec)(const char *__path);
}	t_cd;

#endif