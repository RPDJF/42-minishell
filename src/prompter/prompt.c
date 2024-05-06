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
		prompt = ft_strreplace_first(prompt, home, "~");
		gfree(tmp);
	}
	gfree(home);
	return (prompt);
}

static char	*get_prompt(void)
{
	char		*output;
	char		cwd[PATH_MAX];
	static char	*user;

	getcwd(cwd, PATH_MAX);
	if (!user)
		user = get_var_value("USER");
	output = ft_strsjoin(11, get_userinfo(), "└─", C_CYAN, "[", cwd, "]",
			C_RESET, " [", get_var("?")->value, "]-", ENDLINE);
	if (!output)
		crash_exit();
	output = parse_prompt(output);
	if (!output)
		crash_exit();
	return (output);
}

static char	*script_prompt(void)
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

bool	is_valid_input(char *input)
{
	if (!*input)
	{
		gfree(input);
		return (false);
	}
	while (*input)
	{
		if (!ft_isspace(*input))
			return (true);
		input++;
	}
	gfree(input);
	return (false);
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
		input = addgarbage(readline(strprompt));
		get_minishell()->sigint = 0;
		gfree(strprompt);
		if (!input)
			write(STDERR_FILENO, "exit\n", 5);
		if (!input)
			secure_exit(0);
		if (!is_valid_input(input))
			continue ;
		add_history(input);
		ms_write_history(input);
		return (input);
	}
}
