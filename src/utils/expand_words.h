#ifndef EXPAND_WORDS_H
# define EXPAND_WORDS_H

# include "../minishell.h"
# include "../env/env.h"

//	parse_words: parse words into a single char * and expand variables
char	*parse_words(t_word *words);
//	parse_words_arr: parse words ** into a char ** array
char	**parse_words_arr(t_word **words);
//	words_arr_len:	get the length of a t_word ** array
size_t	words_arr_len(t_word **words);
//	words_strlen:	get the length of a string of t_word * list
size_t	words_strlen(t_word *words);
//	varlen:	get the length of a variable name
size_t	varlen(char *str);

#endif
