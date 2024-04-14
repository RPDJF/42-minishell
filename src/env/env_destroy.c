#include "env.h"

// TO DO: IMPLEMENT TOKEN DESTROY

void	destroy_var(t_var *var)
{
	if (var->name)
		gfree(var->name);
	if (var->type == var_str && var->data)
		gfree(var->data);
	else if (var->type == var_token && var->data)
		printf("data from %s isn't destroyed,\
			token destroy isn't implemented yet\n", var->name);
	gfree(var);
}
