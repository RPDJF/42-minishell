/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:10:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/11 15:29:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_finder.h"

static char	*get_fulpath(char *binary)
{
	char	*tmp;
	char	**path;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		crash_exit();
	i = -1;
	while (path[++i])
	{
		if (!*(strrchr(path[i], '/') + 1))
			tmp = ft_strjoin(path[i], binary);
		else
			tmp = ft_strsjoin(3, path[i], "/", binary);
		if (!tmp)
			crash_exit();
		if (access(tmp, O_RDONLY | O_EXCL) == 0)
		{
			ft_free_tab(path);
			return (tmp);
		}
		free(tmp);
	}
	return (0);
}

char	*find_binary(char *binary)
{
	char	*output;

	output = 0;
	if (ft_strchr(binary, '/'))
	{
		if (access(binary, O_RDONLY | O_EXCL) == 0)
		{
			output = ft_strdup(binary);
			if (!output)
				crash_exit();
		}
	}
	else
		output = get_fulpath(binary);
	return (output);
}
