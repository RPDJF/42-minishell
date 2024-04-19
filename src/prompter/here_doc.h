#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../minishell.h"
# include <readline/readline.h>
# include "history.h"
# include "../executor/executor.h"

//	here_doc:	function that reads from stdin until a delimiter is found
//	return:	fd of a pipe that contains the input read
int	here_doc(char *delimiter);

#endif