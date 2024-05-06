#include "prompt.h"

char	*get_userinfo(void)
{
	static char		*userinfo;
	t_var			*user;

	if (!userinfo)
	{
		user = get_var("USER");
		if (get_minishell()->hostname && user && user->value && *user->value)
			userinfo = ft_strsjoin(11, "\n┌─", C_MAGENTA, "[",
					get_var("USER")->value, " @ ",
					get_minishell()->hostname, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n");
		else if (user && user->value && *user->value)
			userinfo = ft_strsjoin(9, "\n┌─", C_MAGENTA, "[",
					get_var("USER")->value, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n");
		else
			userinfo = ft_strsjoin(11, "\n┌─", C_MAGENTA, "[",
					APP_NAME, "-", VERSION, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n");
		if (!userinfo)
			crash_exit();
	}
	return (userinfo);
}
