#ifndef HISTORY_H
# define HISTORY_H

# include "../minishell.h"
# include "../env/env.h"
# include <readline/history.h>

//	macros
//		File definitions
# define MINISHELL_HISTORY ".minishell_history"

//	ms_write_history:	writes the char* input into history file
//	returns null on success
int	ms_write_history(char *input);
//	ms_load_history:	loads RL history from the history file
//	returns null on success
int	ms_load_history(void);

#endif