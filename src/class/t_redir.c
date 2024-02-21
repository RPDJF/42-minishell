/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:06:39 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/21 17:33:56 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_type	init_redir(char *content, t_redir **redir)
{
	(*redir)->content = content;
	if (!ft_strncmp(content, "|", ft_strlen(content)))
	{
		if (pipe((*redir)->fd))
		{
			free(*redir);
			*redir = 0;
			perror(strerror(errno));
			return (-1);
		}
		return (TYPE_PIPE);
	}
	return (-1);
}

t_redir	*new_redir(char *content)
{
	t_redir	*redir;

	redir = galloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->content = 0;
	redir->limiter = 0;
	redir->tmp_file = 0;
	redir->type = init_redir(content, &redir);
	if (!redir)
		return (0);
	return (redir);
}
