#include "expand_words.h"

static void	replace_word(t_word *word, char *var_name)
{
	t_var	*var;
	char	*expand;
	char	*tmp;

	tmp = word->str;
	var = get_var(var_name + 1);
	if (var)
		expand = var->value;
	else
		expand = "";
	word->str = ft_strreplace(word->str, var_name, expand);
	gfree(tmp);
}

static t_word	*expand_vars(t_word *words)
{
	t_word	*head;
	char	*var_name;
	int		i;
	char	*cursor;

	head = words;
	while (words)
	{
		i = -1;
		while (i++, words->is_var && ft_strchr(words->str + i, '$'))
		{
			cursor = ft_strchr(words->str + i, '$');
			if (!cursor)
				break ;
			if (!(ft_isalnum(*(cursor + 1)) || *(cursor + 1) == '_'
					|| *(cursor + 1) == '?'))
				continue ;
			var_name = ft_substr(cursor, 0, varlen(cursor));
			replace_word(words, var_name);
			gfree(var_name);
			i = -1;
		}
		words = words->next;
	}
	return (head);
}

static t_word	*expand_words(t_word *words)
{
	char	*str;
	char	*home;

	words = expand_vars(words);
	if (*words->str == '~' && !words->is_quoted && (
			(words->str[1] == '/')
			|| (!words->str[1] && !words->next)))
	{
		home = get_var_value("HOME");
		str = words->str;
		words->str = ft_strreplace_first(words->str, "~", home);
		gfree(home);
		gfree(str);
	}
	return (words);
}

size_t	varlen(char *str)
{
	size_t	len;

	len = 1;
	if (str[1] == '?')
		return (len + 1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

char	*parse_words(t_word *words)
{
	char	*output;
	t_word	*head;
	size_t	len;
	char	*tmp;

	words = expand_words(words);
	head = words;
	len = words_strlen(words);
	output = ft_calloc(len, sizeof(char));
	if (!output)
		crash_exit();
	while (head)
	{
		tmp = output;
		output = ft_strjoin(output, head->str);
		if (!output)
			crash_exit();
		if (*tmp)
			gfree(tmp);
		head = head->next;
	}
	return (output);
}
