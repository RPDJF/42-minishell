/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:17:24 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

void	*ft_reallocf(void *ptr, size_t size, size_t newsize)
{
	unsigned char	*old_alloc;
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (ptr == 0)
		return (galloc(newsize));
	old_alloc = (unsigned char *)ptr;
	new_alloc = (unsigned char *)galloc(newsize);
	if (new_alloc == 0)
	{
		gfree(ptr);
		return (0);
	}
	while (i < size && i < newsize)
	{
		new_alloc[i] = old_alloc[i];
		i++;
	}
	gfree(ptr);
	return (new_alloc);
}
