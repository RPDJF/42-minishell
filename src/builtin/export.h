#ifndef EXPORT_H
# define EXPORT_H

# include "../minishell.h"
# include "../env/env.h"

# define EXPORT_OPTIONS ""

// ERROR MESSAGES
# define NOT_VALID_IDENTIFIER "not a valid identifier"

//	export: builtin export command
int	export_ms(int argc, char **argv);

#endif