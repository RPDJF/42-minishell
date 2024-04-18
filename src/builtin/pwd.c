#include "pwd.h"

int	pwd(int argc, char **argv)
{
	char	pwd_str[PATH_MAX];

	(void)argc;
	(void)argv;
	getcwd(pwd_str, PATH_MAX);
	printf("%s\n", pwd_str);
	return (0);
}
