/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:01:57 by ilyanar           #+#    #+#             */
/*   Updated: 2024/02/19 14:45:08 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	*join_cmd_path(char *av, char *env)
{
	int		i;
	int		k;
	char	*cmd;

	i = -1;
	k = ft_strlen(av) + ft_strlen(env) + 2;
	cmd = ft_calloc(k, sizeof(char));
	if (!cmd)
		return (NULL);
	while (env[++i])
		cmd[i] = env[i];
	cmd[i] = '/';
	k = -1;
	while (av[++k] && av[k] > 32)
		cmd[++i] = av[k];
	if ((k <= 0) || (av[ft_strlen(av) - 1] == 32))
	{
		cmd[ft_strlen(env) + 1] = 32;
		return (cmd);
	}
	return (cmd);
}

int	ft_count_tab(char *av)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (av[++i])
	{
		if (av[i] == 32)
		{
			while (av[i] == 32)
				i++;
			j++;
		}
		else if (av[i] == 39)
		{
			while (av[++i])
			{
				if (av[i] == 39 || av[i] == '\0')
					j++;
				if (av[i] == 39 || av[i] == '\0')
					break ;
			}
		}
	}
	return (j);
}
