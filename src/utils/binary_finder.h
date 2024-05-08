/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:48 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_FINDER_H
# define BINARY_FINDER_H

# include "../minishell.h"
# include "../env/env.h"

//	find_binary:  Retrieves the binary path from envp or local path
char	*find_binary(char *binary);

#endif