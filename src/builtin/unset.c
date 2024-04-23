#include "unset.h"

int	unset(int argc, char **argv)
{
	(void)argc;
	while (++argv, *argv)
		remove_var(get_var(*argv));
	return (0);
}
