#include "executor.h"

int	get_wexistatus(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	return (status);
}
