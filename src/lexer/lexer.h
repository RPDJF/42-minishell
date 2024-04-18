#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

typedef struct s_lex
{
	int		i;
	int		j;
}	t_lex;

typedef struct s_tlex
{
	struct s_word	*cmd;
	struct s_tlex	*next;
	struct s_tlex	*prev;
}	t_tlex;

// Return a lexer t_tlex ** struct of the actuel input.
t_tlex	*lexer(char *input);

// Fonction for lexing the quotes
void	end_single_quote(t_lex *lex, char *input, t_tlex **tlex, char *word);
void	single_quote(t_lex *lex, char *input, t_tlex **tlex);
void	end_double_quote(t_lex *lex, char *input, t_tlex **tlex, char *word);
void	double_quote(t_lex *lex, char *input, t_tlex **tlex);

// Create a new tword* noeud and return it.
t_word	*tword_new(char *cmd, bool var);
// returns a linked list of linked list of the input given to it.
t_tlex	*lexer(char *input);
// Add at the end of the t_lex list <lst> the new noeud <neww>.
void	tlex_add_back(t_tlex **lst, t_tlex *neww);
// Add at the end of the t_word list <*cmd> inside the thelist <lst> the new noeud <neww>.
void	tword_add_back(t_tlex **lst, t_word *neww);
// Return 1 if the actuel <str[i]> is a delimiter. else return 0.
int		ft_isdelem(char *str, int i);
int		impair_pair_char(char *str, char c);
void	delem(t_lex *lex, char *input, t_tlex **tlex);
void	delem_bonus(t_lex *lex, char *input, t_tlex **tlex);
void	add_word_to_lex_str(t_lex *lex, char *input, t_tlex **tlex);
void	words_lexing(t_lex *lex, char *input, t_tlex **tlex);

#endif
