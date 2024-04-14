#ifndef BINARY_FINDER_H
# define BINARY_FINDER_H

# include "../minishell.h"
# include "../env/env.h"

//	find_binary:  Retrieves the binary path from envp or local path
char	*find_binary(char *binary);

#endif