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

void	print_userinfo(void)
{
	static char		*userinfo;
	t_var			*user;
	static size_t	bytes;

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
		bytes = ft_strlen(userinfo);
	}
	write(STDOUT_FILENO, userinfo, bytes);
}

static char	*get_prompt(void)
{
	char		*output;
	char		cwd[PATH_MAX];
	static char	*user;

	getcwd(cwd, PATH_MAX);
	if (!user)
		user = get_var_value("USER");
	output = ft_strsjoin(10, "└─", C_CYAN, "[", cwd, "]",
			C_RESET, " [", get_var("?")->value, "]-", ENDLINE);
	if (!output)
		crash_exit();
	output = parse_prompt(output);
	if (!output)
		crash_exit();
	return (output);
}

char	*script_prompt(void)
{
	char		*input;
	char		*trim;

	while (true)
	{
		input = addgarbage(ft_get_next_line(STDIN_FILENO));
		if (!input)
			secure_exit(0);
		trim = ft_strtrim(input, " \t\v\f\r\n");
		if (*trim == '#' || !*trim)
		{
			gfree(input);
			gfree(trim);
			continue ;
		}
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
		strprompt = get_prompt();
		rl_on_new_line();
		rl_replace_line("", 0);
		print_userinfo();
		input = addgarbage(readline(strprompt));
		get_minishell()->sigint = 0;
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
