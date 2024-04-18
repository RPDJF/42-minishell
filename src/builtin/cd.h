#ifndef CD_H
# define CD_H

# include "../minishell.h"
# include "../env/env.h"

typedef struct s_cd
{
	int		argc;
	char	**argv;
	char	*pwd;
	char	pwd_buff[PATH_MAX];
	char	oldpwd[PATH_MAX];
	int		(*exec)(struct s_cd *cd);
}	t_cd;

//	cd: change directory
int	cd(int argc, char **argv);

#endif