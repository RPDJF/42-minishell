#ifndef PROMPT_H
# define PROMPT_H

# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../env/env.h"
# include "history.h"

# define ENDLINE "❥ "

# include "../utils/colors.h"

// Functions
//	prompt: sends a prompt to the user and returns their input as char*
char	*prompt(t_minishell *minishell);

#endif