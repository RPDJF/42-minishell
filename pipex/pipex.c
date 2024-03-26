/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:03:25 by ilyanar           #+#    #+#             */
/*   Updated: 2024/02/21 13:00:17 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_rui(t_pipe *t_main, char *av)
{
	if (t_main->exit_value < 0)
	{
		if (access(av, F_OK) != -1)
			ft_printf("I didn't manage the path directly :)\n");
		else
			ft_printf("pipex: command not found: %s\n", av);
		exit(127);
	}
	if (dup2(t_main->pipes1[0], STDIN_FILENO) < 0)
		ft_strerror("dup 2", 1, NULL, t_main);
	close(t_main->pipes1[0]);
	close(t_main->pipes2[0]);
	if (t_main->last == 1)
	{
		if (dup2(t_main->out_fd, STDOUT_FILENO) < 0)
			ft_strerror("dup 2", 1, NULL, t_main);
		close(t_main->out_fd);
		t_main->in_fd = -2;
	}
	else
		if (dup2(t_main->pipes2[1], STDOUT_FILENO) < 0)
			ft_strerror("dup 2", 1, NULL, t_main);
	close(t_main->pipes2[1]);
}

void	ft_mayon(t_pipe *t_main, char *av)
{
	if (t_main->exit_value < 0)
	{
		if (access(av, F_OK) != -1)
			ft_printf("I didn't manage the path directly :)\n");
		else
			ft_printf("zsh command not found: %s\n", av);
		exit(127);
	}
	if (t_main->in_fd != -2)
	{
		if (dup2(t_main->in_fd, STDIN_FILENO) < 0)
			ft_strerror("dup 2", 1, NULL, t_main);
		close(t_main->in_fd);
	}
	close(t_main->pipes1[0]);
	if (dup2(t_main->pipes1[1], STDOUT_FILENO) < 0)
		ft_strerror("dup 2", 1, NULL, t_main);
	close(t_main->pipes1[1]);
}

void	ft_maria(char **env, t_pipe *t_main, t_list **pid, char *av)
{
	pid_t	*pidt;

	pidt = ft_calloc(1, sizeof(pid_t));
	pidt[0] = fork();
	if (pidt[0] == 0)
	{
		if (t_main->in_fd == -1)
			exit(1);
		ft_mayon(t_main, av);
		execve(t_main->path, t_main->args, env);
		ft_strerror("Execve error", 0, NULL, t_main);
	}
	else
	{
		ft_lstadd_back(pid, ft_lstnew(&pidt[0]));
		close(t_main->pipes1[1]);
	}
}

void	ft_fabien(char **env, t_pipe *t_main, t_list **pid, char *av)
{
	pid_t	*pidt;

	pidt = ft_calloc(1, sizeof(pid_t));
	pidt[0] = fork();
	if (pidt[0] == 0)
	{
		ft_rui(t_main, av);
		execve(t_main->path, t_main->args, env);
		ft_strerror("Execve error", 0, NULL, t_main);
	}
	else
	{
		ft_lstadd_back(pid, ft_lstnew(&pidt[0]));
		close(t_main->pipes2[1]);
		close(t_main->pipes1[0]);
	}
}

int	pipex(char **av, char **envp, t_pipe *t_main, t_list *pid)
{
	int		pair_impar;
	char	*av_actuel;

	pair_impar = 1;
	pipe(t_main->pipes1);
	while (*av && *(av + 1) != NULL)
	{
		av_actuel = *av;
		ft_init_cmd(av++, t_main);
		if (pair_impar == 1)
			ft_maria(envp, t_main, &pid, av_actuel);
		if (pair_impar == 1)
			pair_impar = 0;
		else if (pair_impar == 0)
		{
			pipe(t_main->pipes2);
			if (*(av + 1) == NULL)
				t_main->last = 1;
			ft_fabien(envp, t_main, &pid, av_actuel);
			*t_main->pipes1 = *t_main->pipes2;
		}
		ft_free_char(t_main, 0);
	}
	ft_free_char(t_main, 1);
	return (wait_process(&pid));
}
