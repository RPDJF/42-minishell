#include "../betterft.h"

static size_t	count_replaces(char *src, char *old)
{
	size_t	count;
	char	*tmp;

	count = -1;
	tmp = ft_strnstr(src, old, ft_strlen(src));
	while (count++, tmp && *tmp)
		tmp = ft_strnstr(tmp + 1, old, ft_strlen(tmp + 1));
	return (count);
}

static void	fill_str(char *src, char *old, char *new, char *output)
{
	char	*tmp;
	size_t	size;

	size = 0;
	tmp = ft_strnstr(src, old, ft_strlen(src));
	ft_strlcpy(output + size, src, tmp - src + 1);
	size += tmp - src;
	src += tmp - src;
	ft_strlcpy(output + size, new, ft_strlen(new) + 1);
	size += ft_strlen(new);
	src += ft_strlen(old);
	tmp = ft_strnstr(tmp + 1, old, ft_strlen(tmp + 1));
	ft_strlcpy(output + size, src, tmp - src + 1);
}

char	*ft_strreplace_first(char *src, char *old, char *new)
{
	char	*output;
	int		count;
	size_t	size;

	count = count_replaces(src, old);
	if (!count)
		return (ft_strdup(src));
	size = ((ft_strlen(src) + (ft_strlen(new) - ft_strlen(old))) + 1);
	output = galloc(size);
	if (!output)
		return (0);
	fill_str(src, old, new, output);
	return (output);
}
