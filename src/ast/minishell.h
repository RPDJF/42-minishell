/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:29:32 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/01 19:13:45 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libs/betterft/betterft.h"
# include "utils/colors.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

//	structs

typedef enum e_node_type
{
	e_cmd,
	e_pipe,
	e_and_or
}	t_type;

typedef struct s_astnode
{
	t_type				type;
	char				**args;
	struct s_astnode	*l_node;
	struct s_astnode	*r_node;
}					t_astnode;

typedef struct s_minishell
{
	bool		hasenv;
	char		*hostname;
	t_astnode	*astnode;
}				t_minishell;

//	functions

//	in file utils/astnode.c

//		new_astnode: init a new astnode
t_astnode	*new_astnode(char **args, t_type type);

//		error_handler: handle exits and errors

//	in file utils/faker.c

//		generate_fake_ast: generate a fake ast
t_astnode	*generate_fake_ast(void);

//	in file utils/minishell_init.c

//		minishell_init: init a new minishell instance
t_minishell	*minishell_init(void);

//	in file utils/prompter.c

//		start_prompt: start a new prompt loop
void		start_prompt(t_minishell *minishell);

#endif