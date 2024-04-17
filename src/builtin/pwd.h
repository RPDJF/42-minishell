#ifndef PWD_H
# define PWD_H

# include "../minishell.h"
# include "../env/env.h"

# define PWD_OPTIONS ""

typedef struct s_pwd
{
	int		argc;
	char	**argv;
	void	(*exec)(char *str, int fd);
}	t_pwd;

//	pwd: builtin pwd command
int	pwd(int argc, char **argv);

#endif