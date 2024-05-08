/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:18 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:18 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*parse_prompt(char *prompt)
{
	t_var	*home;
	char	*tmp;
	char	*tmp2;

	if (!prompt)
		return (0);
	home = get_var("HOME");
	if (home && home->value && *home->value)
	{
		tmp = prompt;
		tmp2 = ft_strjoin("└─"C_CYAN"[", home->value);
		if (!tmp2)
			crash_exit();
		prompt = ft_strreplace_first(prompt, tmp2, "└─"C_CYAN"[~");
		if (!prompt)
			crash_exit();
		gfree(tmp2);
		gfree(tmp);
	}
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
	output = ft_arrjoin((char *[]){get_userinfo(), "└─", C_CYAN, "[", cwd, "]",
			C_RESET, " [", get_var("?")->value, "]-", ENDLINE, 0});
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
		input = ft_get_next_line(STDIN_FILENO);
		if (!input)
			secure_exit(0);
		trim = ft_strtrim(input, " \t\v\f\r\n");
		if (*trim == '#' || !*trim)
			continue ;
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
