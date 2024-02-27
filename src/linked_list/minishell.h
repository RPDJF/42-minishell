/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:34:15 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/27 15:49:37 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../libs/betterft/betterft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>

typedef int	t_type;

# define TYPE_CMD 0
# define TYPE_REDIR 1
# define TYPE_PIPE 2

typedef struct s_token
{
	int				id;
	t_type			type;
	void			*s_class;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_arg
{
	int				id;
	char			*content;
	struct s_arg	*prev;
	struct s_arg	*next;
}				t_arg;

// classes

typedef struct s_cmd
{
	int		id;
	char	*content;
	char	*flags;
	char	*bin;
	char	**args;
	char	*arg;
	int		fd_in;
	int		fd_out;
	t_arg	*first_arg;
	pid_t	pid;

}		t_cmd;

typedef struct s_file
{
	char	*name;
	int		fd;
}		t_file;

typedef struct s_redir
{
	int		fd[2];
	t_type	type;
	char	*limiter;
	char	*content;
	t_file	*tmp_file;
}		t_redir;

typedef struct s_word
{
	char *content;
}		t_word;

// functions

//	new_cmd: creates and inits a new cmd class
t_cmd	*new_cmd(int id, char *content, char **args);
//	new_redir: creates and inits a new redir class
t_redir	*new_redir(char *content);

#endif