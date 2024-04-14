#ifndef ECHO_H
# define ECHO_H

# include "../minishell.h"

# define OPTIONS "n"

typedef struct s_echo
{
	bool	has_newline;
	int		argc;
	char	**argv;
	void	(*exec)(char *str, int fd);
}	t_echo;

//	echo: builtin echo command
int	echo(int argc, char **argv);

#endif