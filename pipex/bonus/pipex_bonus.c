/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:28:10 by ilyanar           #+#    #+#             */
/*   Updated: 2024/02/21 15:28:26 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>

void	ft_here_doc(char **av, t_pipe *t_main)
{
	int		fd;
	char	*str;

	fd = open("bonus/tmp", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(127);
	}
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (ft_memcmp(av[2], str, ft_strlen(av[2])) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	fd = open("bonus/tmp", O_RDONLY);
	t_main->in_fd = fd;
}

void	ft_init_bonus(char **av, t_pipe *t_main)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		ft_here_doc(av, t_main);
	else
		t_main->in_fd = open(av[1], O_RDONLY);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	t_main;
	t_list	*pid;
	int		status;

	pid = NULL;
	status = 127;
	if ((ac < 5))
		ft_printf("less arg than 5");
	else
	{
		init_path(&t_main, envp);
		if (access(av[ac - 1], W_OK) != 0)
			unlink(av[ac - 1]);
		t_main.out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_init_bonus(av, &t_main);
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
			av += 3;
		else
			av += 2;
		status = pipex(av, envp, &t_main, pid);
		close(t_main.in_fd);
		unlink("bonus/tmp");
	}
	exit (status);
}
