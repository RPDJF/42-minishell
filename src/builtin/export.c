#include "export.h"

static bool	is_valid_name(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

static int	fn(char *str)
{
	char	*name;
	char	*value;

	name = ft_strchr(str, '=');
	if (!name)
	{
		name = ft_strdup(str);
		value = 0;
	}
	else
	{
		name = ft_substr(str, 0, name - str);
		if (!name)
			crash_exit();
		value = ft_strdup(ft_strchr(str, '=') + 1);
		if (!value)
			crash_exit();
	}
	if (!is_valid_name(name))
	{
		str = ft_strsjoin(3, "`", str, "'");
		error_msg((char *[]){APP_NAME, "export", str, 0}, NOT_VALID_IDENTIFIER);
		return (1);
	}
	update_var(new_var(name, value, true, true));
}

int	export_ms(int argc, char **argv)
{
	int		status;

	status = 0;
	if (argc == 1)
	{
		print_export();
		return (status);
	}
	argv++;
	while (*argv)
	{
		if (!status)
			status = fn(*argv);
		else
			fn(*argv);
		argv++;
	}
	return (status);
}
