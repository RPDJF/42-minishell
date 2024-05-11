/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:25:25 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static bool	is_valid_name(char *str)
{
	if (ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

char	*var_name(char *str)
{
	char	*name;

	name = ft_strchr(str, '=');
	if (name == str)
		return (0);
	if (!name)
		name = ft_strdup(str);
	else
		name = ft_substr(str, 0, name - str);
	return (name);
}

static char	*var_value(char *str)
{
	char	*value;

	value = ft_strchr(str, '=');
	if (!value)
		value = 0;
	else
		value = ft_strdup(value + 1);
	return (value);
}

static int	fn(char *str)
{
	char	*name;
	char	*value;

	name = var_name(str);
	if (!name || !is_valid_name(name))
	{
		str = ft_arrjoin((char *[]){"'", str, "'", 0});
		error_msg((char *[]){APP_NAME, "export", str, 0}, NOT_VALID_IDENTIFIER);
		if (name)
			gfree(name);
		gfree(str);
		return (1);
	}
	value = var_value(str);
	update_var(new_var(name, value, true, true));
	return (0);
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
