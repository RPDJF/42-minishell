/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:55 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/08 18:48:36 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lexer/lexer.h"

typedef struct s_pars
{
	int		i;
	int		j;
	t_tlex	*tmp1;
}	t_pars;

t_token			*parsing(t_tlex **lex);
//	free a t_cmd struct
void			free_cmd(t_cmd	*data);
//	free a t_stdout struct
void			free_stdout(t_stdout *data_stdout);
//	free a t_stdin struct
void			free_stdin(t_stdin *data_stdin);
//	free a t_var_init struct
void			free_is_var(t_var_init *data);
//	free the entire linked list t_token ** and t_tlex lexer
t_token			*free_exit_token(t_token **token, t_tlex **lex);
//	returns a token * of token of a t rex lexer, it is a linked list of tokens
t_token			*parsing(t_tlex **lex);
//	free a t_word struct
void			free_tword(t_word *cmd);
//	returns the first occurrence of int C in tword * cmd
char			*tw_strchr(t_word *cmd, int c);
//	Count the numbers of noeud of the t_tlex linked list
int				arg_count(t_tlex *arg);
//	return "NULL", use "error_msg()" and "update_exit_code()";
void			*exit_tk(char **context, char *msg, int exitcode);
//	return (1) if in the prev noeud of the "t_word *cmd"
//	is_quoted==true, else return (0).
bool			prev_quoted(t_word	*cmd);
//	return (1) if the function found a varable assignement
//	"ex:a=b" and if the "is_quoted==0"
//	else return (0).
int				var_quoted(t_word *cmd);
//	init a t_var_init token to the "neww" t_token.
int				tk_is_var_init(t_token *neww, t_pars *pars);
//	add the t_token "neww" at the end of "token".
t_token			**token_add_back(t_token **token, t_token *neww);
//	return (1) if cmd->str is "| or || or &&"
//	return (2) if cmd->str is "< or << or >> or>"
//	else return (0);
int				tw_is_delem(t_word *cmd);
//	returns a dynamically allocated char *
//	which is the concatenation of all the char *strs in the t_word "cmd".
char			*join_tword(t_word	*cmd);
//	the final part of the newwtk_delem
t_token			*end_newtk_delem2(t_word *cmd, t_pars *pars, t_token *neww);
//	the second part of the newwtk_delem
t_token			*end_newtk_delem(t_word *cmd, t_pars *pars, t_token *neww);
//	return a token "t_token *" if the t_word "cmd" is a delemiter
t_token			*newwtk_delem(t_word *cmd, t_pars *pars);
//	the function calculates and adds the arguments of
//	the cmd previously found to the t_word token->argv** if the function 
//	encounters a redirection it cuts the redirection and uses 
//	token_add_back() to add it to the end of the current token
//	return (0) if an error is encountered.
int				pars_arg_tk_cmd(t_token *neww, t_cmd *token, t_pars *pars);
//	parse the current t_token into a cmd token
//	return (0) if an error is encountered.
int				tk_cmd(t_token *neww, t_pars *pars);
//	returns a dynamically allocated new *token.
t_token			*token_new(t_pars *pars);
//	parse the current t_token into a token delemiter for "|" "||" and "&&"
//	return (0) if an error is encountered.
int				tk_delem(t_token *neww, t_pars *pars);
//	return (true) if any cmd->str in the cmd list contains a quote
//	else return (false);
bool			is_it_quoted(t_word *cmd);
//	return the type of the cmd
t_token_type	define_type(t_word *cmd);
//	check if the var str have a correct syntax (only alphanumeric caratere)
int				correct_syntax_var(char *str);
//	check if the actuel t_word is a subshell.
int				is_subshell(t_word *cmd);
//	creat subshell tokens.
int				tk_subshell(t_token *neww, t_pars *pars);
//	Check the right syntaxe of the tokens with subshell.
void			*check_syntax_subshell(t_token *token);
int				token_syntax(t_token *token);
int				tk_delem_syntax(t_word *cmd, bool print);
int				syntax_redirection(t_word *cmd, bool print);
void			free_all(t_token **token, t_tlex **lex);
int				syntax_at_end(t_token *token);

#endif
