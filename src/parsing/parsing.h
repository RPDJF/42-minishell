#ifndef PARSING_H
# define PARSING_H

# include "../lexer/lexer.h"

t_token	*parsing(t_tlex **lex);

typedef struct s_pars
{
	int		i;
	int		j;
	t_tlex	*tmp1;
	t_tlex	*tmp2;
}	t_pars;

void	free_cmd(t_cmd	*data);
void	free_stdout(t_stdout *data_stdout);
void	free_stdin(t_stdin *data_stdin);
void	free_is_var(t_var_init *data);
t_token	*free_exit_token(t_token **token, t_tlex **lex);
t_token	*parsing(t_tlex **lex);
void	free_tword(t_word *cmd);
char	*tw_strchr(t_word *cmd, int c);

#endif
