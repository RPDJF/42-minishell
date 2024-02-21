/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsuperclear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:57:23 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

void	ft_memsuperclear(void **m, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		gfree(m[i++]);
	gfree(m);
}
