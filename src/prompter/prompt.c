#include "prompt.h"

static char	*parse_prompt(char *prompt)
{
	char	*home;
	char	*tmp;

	home = get_var_value("HOME");
	if (*home)
	{
		tmp = prompt;
		prompt = ft_strreplace(prompt, home, "~");
		gfree(tmp);
	}
	gfree(home);
	return (prompt);
}

static char	*get_prompt(t_minishell *minishell)
{
	char	*output;
	char	*cwd;
	char	*user;

	cwd = getcwd(0, 0);
	if (!cwd)
		crash_exit();
	user = get_var_value("USER");
	if (minishell->hostname && user)
		output = ft_strsjoin(10, C_MAGENTA, user, "@",
				minishell->hostname, C_RESET, ":", C_CYAN,
				cwd, C_RESET, ENDLINE);
	else if (user)
		output = ft_strsjoin(8, C_MAGENTA, user,
				C_RESET, ":", C_CYAN, cwd, C_RESET, ENDLINE);
	else
		output = ft_strsjoin(8, C_MAGENTA, "minishell-", C_CYAN, VERSION,
				C_RESET, ":", cwd, ENDLINE);
	if (!output)
		crash_exit();
	gfree(cwd);
	gfree(user);
	output = parse_prompt(output);
	return (output);
}

char	*prompt(t_minishell *minishell)
{
	char	*input;
	char	*strprompt;

	ms_load_history();
	while (true)
	{
		strprompt = get_prompt(minishell);
		if (!strprompt)
			return (0);
		input = 0;
		input = readline(strprompt);
		if (!input)
			continue ;
		if (*input && !ft_isspace(*input))
			add_history(input);
		gfree(strprompt);
		if (ms_write_history(input))
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (input);
	}
}
