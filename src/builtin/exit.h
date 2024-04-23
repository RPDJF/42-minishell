#ifndef EXIT_H
# define EXIT_H

# include "../minishell.h"
# include "../env/env.h"
# include <readline/readline.h>

//	exit_ms: builtin exit command
int	exit_ms(int argc, char **argv);

#endif