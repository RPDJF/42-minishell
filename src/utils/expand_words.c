#include "expand_words.h"

static size_t	varlen(char *str)
{
	size_t	len;

	len = 1;
	if (str[1] == '?')
		return (len + 1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

void	replace_word(t_word *word, char *var_name)
{
	t_var	*var;
	char	*expand;
	char	*tmp;

	tmp = word->str;
	var = get_var(var_name + 1);
	if (var)
	{
		if (var->type == var_str)
			expand = var->data;
		else
			expand = "TOKEN_VAR_NOT_IMPLEMENTED_YET";
	}
	else
		expand = "";
	word->str = ft_strreplace(word->str, var_name, expand);
	gfree(tmp);
}

static t_word	*expand_words(t_word *words)
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
			i = -1;
		}
		words = words->next;
	}
	return (head);
}

char	*parse_words(t_word *words)
{
	char	*output;
	t_word	*head;
	size_t	len;
	char	*tmp;

	words = expand_words(words);
	head = words;
	len = 1;
	while (words)
	{
		len += ft_strlen(words->str);
		words = words->next;
	}
	output = ft_calloc(len, sizeof(char));
	if (!output)
		crash_exit();
	while (head)
	{
		tmp = output;
		output = ft_strjoin(output, head->str);
		if (*tmp)
			gfree(tmp);
		head = head->next;
	}
	return (output);
}
