#include "env.h"

void	destroy_var(t_var *var)
{
	if (var->name)
		gfree(var->name);
	if (var->value)
		gfree(var->value);
	gfree(var);
}
