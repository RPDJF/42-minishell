/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:15 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/10 19:30:14 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*get_userinfo(void)
{
	static char		*userinfo;
	t_var			*user;

	if (!userinfo)
	{
		user = get_var("USER");
		if (get_minishell()->hostname && user && user->value && *user->value)
			userinfo = ft_arrjoin((char *[]){"\n┌─", C_MAGENTA, "[",
					get_var("USER")->value, " @ ",
					get_minishell()->hostname, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n", 0});
		else if (user && user->value && *user->value)
			userinfo = ft_arrjoin((char *[]){"\n┌─", C_MAGENTA, "[",
					get_var("USER")->value, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n", 0});
		else
			userinfo = ft_arrjoin((char *[]){"\n┌─", C_MAGENTA, "[",
					APP_NAME, "-", VERSION, "]", C_RESET, " [SHLVL ",
					get_var("SHLVL")->value, "]\n", 0});
	}
	return (userinfo);
}
