#ifndef EXIT_H
# define EXIT_H

# include "../minishell.h"
# include "../env/env.h"

# define EXIT_OPTIONS ""

typedef struct s_exit
{
	int		argc;
	char	**argv;
	void	(*exec)(char **context, char *errmsg, int exitcode);
}	t_exit;

//	exit_ms: builtin exit command
int	exit_ms(int argc, char **argv);

#endif