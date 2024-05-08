/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:38 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:38 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	unset(int argc, char **argv)
{
	(void)argc;
	while (++argv, *argv)
		if (**argv && ft_isalpha(**argv))
			remove_var(get_var(*argv));
	return (0);
}
