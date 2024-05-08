/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:15 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/09 01:06:08 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_WORDS_H
# define EXPAND_WORDS_H

# include "../minishell.h"
# include "../env/env.h"

//	parse_words: parse words into a single char * and expand variables
char	*parse_words(t_word *words);
//	parse_words_arr: parse words ** into a char ** array
char	**parse_words_arr(t_word **words);
//	expand_words_line: expand words into a single char * and expand variables
//	if *, files are expanded and separated by FS (28)
char	*parse_words_line(t_word *words);
//	join_words:	join words into a single char * without expanding them
char	*join_words(t_word *words);
//	words_arr_len:	get the length of a t_word ** array
size_t	words_arr_len(t_word **words);
//	words_strlen:	get the length of a string of t_word * list
size_t	words_strlen(t_word *words);
//	varlen:	get the length of a variable name
size_t	varlen(char *str);
//	expand the variable 
t_word	*expand_words(t_word *words);
//	fonctions for wildcards
//	begining of the parsing of wildcards
char	**pars_wildcard(char *str);
//	return 1 if is the last wildcard, else return 0.
int		is_last_wildcard(char *str);
//	replace all the occurence of * quoted with ascii 5.
void	replace_wildcard(char **str, bool rpls);
//	realloc char **arr with char **wld.
void	realloc_arr(char ***arr, char **wld, size_t *i);
//	get files in the current directory,
char	**get_files(void);

#endif
