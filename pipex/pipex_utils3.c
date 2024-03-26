/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:01:26 by ilyanar           #+#    #+#             */
/*   Updated: 2024/02/21 12:17:36 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>

void	ft_free_char(t_pipe *t_main, int cmd)
{
	if (t_main->path)
		free(t_main->path);
	t_main->path = NULL;
	if (t_main->cmd_alone)
		free(t_main->cmd_alone);
	t_main->cmd_alone = NULL;
	if (t_main->args)
		ft_free_tab(t_main->args);
	t_main->args = NULL;
	t_main->arg = NULL;
	if (cmd > 0)
	{
		if (t_main->env)
		{
			ft_free_tab(t_main->env);
			t_main->env = NULL;
		}
	}
}

void	found_cmd_alone(t_pipe *t_main, char *av)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (av[i] && ft_isprint(av[i]) == 1 && av[i] > 32)
		i++;
	t_main->cmd_alone = ft_calloc(i + 1, sizeof(char));
	if (!t_main->cmd_alone)
		ft_strerror("Error malloc", 0, NULL, t_main);
	while (++j < i)
		t_main->cmd_alone[j] = av[j];
}

int	path_command(char *av, t_pipe *t_main)
{
	int		i;

	i = 0;
	while (t_main->env[i])
	{
		t_main->path = join_cmd_path(av, t_main->env[i]);
		if (access(t_main->path, F_OK) != -1)
			return (t_main->exit_value = 0);
		free(t_main->path);
		t_main->path = NULL;
		i++;
	}
	return (t_main->exit_value = -1);
}

int	is_tring(char *av, char *str)
{
	int	i;

	i = 0;
	while (av[i] == str[i])
	{
		if (str[i] == '\0')
			return (1);
		i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_init_cmd(char **av, t_pipe *t_main)
{
	path_command(*av, t_main);
	found_cmd_alone(t_main, *av);
	parse_arg(t_main, *av);
}
