/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:02 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:25:02 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_exitcode(int exitcode)
{
	char	*tmp;

	tmp = ft_itoa(exitcode);
	if (!tmp)
		crash_exit();
	update_var(new_var("?", tmp, false, false));
}

void	update_dash(char *value)
{
	char	*tmp;

	tmp = value;
	if (!value)
		tmp = ft_strdup("");
	update_var(new_var("_", tmp, false, false));
}
