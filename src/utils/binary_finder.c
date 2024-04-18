#include "binary_finder.h"

static char	**get_patharr(void)
{
	char	*str_path;
	char	**path;

	str_path = get_var_value("PATH");
	path = ft_split(str_path, ':');
	if (!path)
		crash_exit();
	gfree(str_path);
	return (path);
}

static char	*get_fulpath(char *binary)
{
	char	*tmp;
	char	**path;
	int		i;

	path = get_patharr();
	i = -1;
	while (path[++i])
	{
		if (strrchr(path[i], '/') && !*(strrchr(path[i], '/') + 1))
			tmp = ft_strjoin(path[i], binary);
		else
			tmp = ft_strsjoin(3, path[i], "/", binary);
		if (!tmp)
			crash_exit();
		if (!access(tmp, O_EXCL))
		{
			ft_free_tab(path);
			return (tmp);
		}
		gfree(tmp);
	}
	return (binary);
}

char	*find_binary(char *binary)
{
	char	*output;

	output = 0;
	if (ft_strchr(binary, '/'))
	{
		if (access(binary, R_OK) == 0)
		{
			output = ft_strdup(binary);
			if (!output)
				crash_exit();
		}
	}
	else
		output = get_fulpath(binary);
	return (output);
}
