/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:09:56 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/11 13:44:22 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_FINDER_H
# define BINARY_FINDER_H

# include "../minishell.h"

//	find_binary:  Retrieves the binary path from envp or local path
char	*find_binary(char *binary);

#endif