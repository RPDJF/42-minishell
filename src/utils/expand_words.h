#ifndef EXPAND_WORDS_H
# define EXPAND_WORDS_H

# include "../minishell.h"
# include "../env/env.h"

//	parse_words: parse words into a single char * and expand variables
char	*parse_words(t_word *words);

#endif