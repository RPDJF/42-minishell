/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:33 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:34 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

int	pwd(int argc, char **argv)
{
	char	pwd_str[PATH_MAX];

	(void)argc;
	(void)argv;
	getcwd(pwd_str, PATH_MAX);
	printf("%s\n", pwd_str);
	return (0);
}
