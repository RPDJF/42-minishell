/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:10:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/04/03 14:20:44 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_finder.h"

char	*find_binary(char *file)
{
	char	*tmp;
	char	**path;
	if (access(file, O_RDONLY | O_EXCL) == 0)
		return (file);
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		crash_exit();
	while (*path)
	{
		if (strrchr(*path, '/'))
			tmp = ft_strjoin(*path, file);
		else
			tmp = ft_strsjoin(3, *path, "/", file);
		if (!tmp)
			crash_exit();
		if (access(tmp, O_RDONLY | O_EXCL) == 0)
		{
			free(path);
			ft_memsuperclear(path, )
			return (tmp);
		}
		free(tmp);
		path++;
	}
	return (0);
}