/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:49:28 by ilyanar           #+#    #+#             */
/*   Updated: 2023/10/21 14:53:02 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (i++, s[i])
		write(fd, &s[i], 1);
	return ;
}
/*
int	main(void)
{
	char tab[] = "hello";
	ft_putstr_fd(tab, 1);
}
*/
