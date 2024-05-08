/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:05 by ilyanar           #+#    #+#             */
/*   Updated: 2024/05/09 01:03:51 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_words.h"

int	is_last_wildcard(char *str)
{
	if (*str == '*')
		str++;
	while (*str)
	{
		if (*str == '*')
			return (0);
		str++;
	}
	return (1);
}

void	replace_wildcard(char **str, bool rpls)
{
	int	i;
	int	j;

	i = -1;
	while (str && str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == '*' && rpls)
				str[i][j] = 5;
			if (str[i][j] == 5 && !rpls)
				str[i][j] = '*';
		}
	}
}

void	realloc_arr(char ***arr, char **wld, size_t *i)
{
	int	j;

	j = 0;
	if (!*arr[0])
		return ;
	gfree(arr[0][*i]);
	arr[0][*i] = NULL;
	while (wld && wld[j])
	{
		*arr = strr_realloc(*arr, wld[j]);
		gfree(wld[j]);
		j++;
	}
	while (arr[0][*i + 1])
		*i += 1;
}

static DIR	*get_entry(void)
{
	DIR				*dir;
	char			pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	dir = opendir(pwd);
	return (dir);
}

char	**get_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**arr;
	int				i;

	dir = get_entry();
	if (!dir)
		return (NULL);
	i = -1;
	entry = readdir(dir);
	arr = 0;
	while (++i, entry)
	{
		arr = ft_reallocf(arr, i * sizeof(char *), (i + 2) * sizeof(char *));
		if (!arr)
			crash_exit();
		arr[i] = ft_strdup(entry->d_name);
		if (!arr[i])
			crash_exit();
		entry = readdir(dir);
	}
	closedir(dir);
	arr[i] = 0;
	return (arr);
}
