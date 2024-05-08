/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:21 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:21 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVB_H
# define ENVB_H

# include "../minishell.h"
# include "../env/env.h"

//	env: builtin env command
int	env(int argc, char **argv);

#endif