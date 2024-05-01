#include "unset.h"

int	unset(int argc, char **argv)
{
	(void)argc;
	while (++argv, *argv)
		if (**argv && ft_isalpha(**argv))
			remove_var(get_var(*argv));
	return (0);
}
