/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:41:58 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/13 12:10:45 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_lex
{
	int		i;
	int		j;
}	t_lex;

typedef struct s_tlex
{
	bool			var;
	char			*cmd;
	struct s_tlex	*next;
	struct s_tlex	*prev;
}	t_tlex;

// Return a lexer t_tlex ** struct of the actuel input.
t_tlex	*lexer(char *input);

#endif
