#ifndef CD_H
# define CD_H

# include "../minishell.h"
# include "../env/env.h"

typedef struct s_cd
{
	int		argc;
	char	**argv;
	char	*path;
	char	**context;
	int		status;
	int		(*exec)(const char *__path);
}	t_cd;

//	cd: change directory
int	cd(int argc, char **argv, char **envp);

#endif