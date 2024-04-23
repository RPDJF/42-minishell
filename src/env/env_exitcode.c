#include "env.h"

void	update_exitcode(int exitcode)
{
	char	*tmp;

	tmp = ft_itoa(exitcode);
	if (!tmp)
		crash_exit();
	update_var(new_var("?", tmp, false, false));
}
