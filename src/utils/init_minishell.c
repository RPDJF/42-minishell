/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:01 by rude-jes          #+#    #+#             */
/*   Updated: 2024/03/26 19:58:08 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*mini_gethostname(void)
{
	const char	hostname[] = "/etc/hostname";
	char		*output;
	char		*tmp;
	char		*line;
	int			fd;

	fd = open(hostname, O_RDONLY);
	if (fd < 0)
		return (0);
	line = ft_get_next_line(fd);
	output = ft_strdup("");
	while (line)
	{
		if (output)
			tmp = output;
		output = ft_strjoin(output, line);
		if (!output)
			return (0);
		if (tmp)
			free (tmp);
		free(line);
		line = ft_get_next_line(fd);
	}
	output[ft_strlen(output) - 1] = 0;
	return (output);
}

t_minishell	*init_minishell(void)
{
	t_minishell	*minishell;

	minishell = galloc(sizeof(t_minishell));
	if (!minishell)
		return (0);
	minishell->hostname = mini_gethostname();
	return (minishell);
}
