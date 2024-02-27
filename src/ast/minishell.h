/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:32 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/27 16:47:53 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libs/betterft/betterft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_minishell
{
	bool	hasenv;
	char	*hostname;
}				t_minishell;

typedef enum e_node_type{e_cmd, e_pipe, e_and_or}	t_type;

typedef struct s_astnode
{
	t_type				type;
	char				**args;
	struct s_astnode	*l_node;
	struct s_astnode	*r_node;
}					t_astnode;

#endif