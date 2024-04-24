#ifndef PARSING_H
# define PARSING_H

# include "../lexer/lexer.h"

t_token	*parsing(t_tlex **lex);

typedef struct s_pars
{
	int		i;
	int		j;
	t_tlex	*tmp1;
}	t_pars;

void	free_cmd(t_cmd	*data);
void	free_stdout(t_stdout *data_stdout);
void	free_stdin(t_stdin *data_stdin);
void	free_is_var(t_var_init *data);
t_token	*free_exit_token(t_token **token, t_tlex **lex);
t_token	*parsing(t_tlex **lex);
void	free_tword(t_word *cmd);
char	*tw_strchr(t_word *cmd, int c);
int		arg_count(t_tlex *arg);
void	*exit_tk(char **context, char *msg);
int		prev_quoted(t_word	*cmd);
int		var_quoted(t_word *cmd);
int		tk_is_var_init(t_token *neww, t_pars *pars);
t_token	**token_add_back(t_token **token, t_token *neww);
int		tw_is_delem(t_word *cmd);
char	*join_tword(t_word	*cmd);
t_token	*end_newtk_delem2(t_word *cmd, t_pars *pars, t_token *neww);
t_token	*end_newtk_delem(t_word *cmd, t_pars *pars, t_token *neww);
int		pars_arg_tk_cmd(t_token *neww, t_cmd *token, t_pars *pars);
int		tk_cmd(t_token *neww, t_pars *pars);
t_token	*token_new(t_pars *pars);
int		tk_delem(t_token *neww, t_pars *pars);
t_token	*token_neww(t_pars *pars);
t_token	*newwtk_delem(t_word *cmd, t_pars *pars);

#endif
