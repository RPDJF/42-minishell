#include "prompt.h"

static char	*parse_prompt(char *prompt)
{
	char	*home;
	char	*tmp;

	if (!prompt)
		return (0);
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
	char		*output;
	char		*cwd;
	static char	*user;

	cwd = getcwd(0, 0);
	if (!cwd)
		crash_exit();
	if (!user)
		user = get_var_value("USER");
	if (minishell->hostname && *user)
		output = ft_strsjoin(13, C_MAGENTA, user, "@",
				minishell->hostname, C_RESET, ":", C_CYAN,
				cwd, C_RESET, " [", get_var("?")->value, "]-", ENDLINE);
	else if (*user)
		output = ft_strsjoin(11, C_MAGENTA, user,
				C_RESET, ":", C_CYAN, cwd, C_RESET,
				" [", get_var("?")->value, "]-", ENDLINE);
	else
		output = ft_strsjoin(12, C_MAGENTA, APP_NAME, "-", C_CYAN, VERSION,
				C_RESET, ":", cwd, " [", get_var("?")->value, "]-", ENDLINE);
	gfree(cwd);
	output = parse_prompt(output);
	if (!output)
		crash_exit();
	return (output);
}

char	*script_prompt(void)
{
	char		*input;

	while (true)
	{
		input = ft_get_next_line(STDIN_FILENO);
		if (!input)
			secure_exit(0);
		return (input);
	}
}

char	*prompt(t_minishell *minishell)
{
	char		*input;
	char		*strprompt;

	if (minishell->is_script)
		return (script_prompt());
	while (true)
	{
		strprompt = get_prompt(minishell);
		rl_on_new_line();
		rl_replace_line("", 0);
		input = readline(strprompt);
		minishell->sigint = 0;
		gfree(strprompt);
		if (!input)
			write(STDERR_FILENO, "exit\n", 5);
		if (!input)
			secure_exit(0);
		if (!*input || ft_isspace(*input))
			return (input);
		add_history(input);
		ms_write_history(input);
		return (input);
	}
}
