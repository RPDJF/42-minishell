/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:45 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 18:54:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_finder.h"

static char	**get_patharr(void)
{
	char	*str_path;
	char	**path;

	str_path = get_var_value("PATH");
	path = ft_split(str_path, ':');
	if (!path)
		crash_exit();
	gfree(str_path);
	return (path);
}

char	*build_path(char **path, char *binary, int i)
{
	char	*output;

	if (ft_strrchr(path[i], '/') && !*(ft_strrchr(path[i], '/') + 1))
		output = ft_strjoin(path[i], binary);
	else
		output = ft_arrjoin((char *[]){path[i], "/", binary, 0});
	if (!output)
		crash_exit();
	return (output);
}

static char	*get_fulpath(char *binary)
{
	char	*tmp;
	char	**path;
	int		i;

	path = get_patharr();
	i = -1;
	while (path[++i])
	{
		tmp = build_path(path, binary, i);
		if (access(tmp, X_OK) == 0)
		{
			ft_free_tab(path);
			return (tmp);
		}
		gfree(tmp);
	}
	ft_free_tab(path);
	binary = ft_strdup(binary);
	if (!binary)
		crash_exit();
	return (binary);
}

char	*find_binary(char *binary)
{
	char	*output;

	if (!binary)
		return (0);
	else if (!*binary)
		return ("");
	output = 0;
	if (ft_strchr(binary, '/'))
		return (binary);
	else if (get_var("PATH")
		&& get_var("PATH")->value && *get_var("PATH")->value)
		return (get_fulpath(binary));
	else
	{
		access(binary, X_OK);
		return (binary);
	}
	return (output);
}
