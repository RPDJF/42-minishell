/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:19:05 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

char	*ft_memtostr(void *mem, size_t size)
{
	char	eos;

	eos = '\0';
	mem = ft_reallocf(mem, size, size + 1);
	if (!mem)
		return (0);
	((unsigned char *)mem)[size] = eos;
	return ((char *)mem);
}
