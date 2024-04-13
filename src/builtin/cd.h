/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:15:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/13 23:13:37 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../minishell.h"

typedef struct s_cd
{
	int		argc;
	char	**argv;
	char	*path;
	char	**context;
	int		status;
	int		(*exec)(const char *__path);
}	t_cd;

#endif