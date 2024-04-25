#include "executor.h"

pid_t	init_subshell(t_token *tokens)
{
	t_subshell	*subshell;

	subshell = (t_subshell *)tokens->data;
	subshell->pid = fork();
	if (subshell->pid < 0)
		crash_exit();
	if (subshell->pid == 0)
		exit(executor(subshell->token));
	return (subshell->pid);
}