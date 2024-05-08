/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:03 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:05 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../minishell.h"
# include "../env/env.h"

typedef struct s_cd
{
	int		argc;
	char	**argv;
	char	*pwd;
	char	pwd_buff[PATH_MAX];
	char	oldpwd[PATH_MAX];
	int		(*exec)(struct s_cd *cd);
}	t_cd;

//	cd: change directory
int	cd(int argc, char **argv);

#endif