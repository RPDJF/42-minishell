#include "lexer.h"

void	tlex_add_back(t_tlex **lst, t_tlex *neww)
{
	t_tlex	*tmp;

	if (!lst || !neww)
		return ;
	if (!*lst)
		*lst = neww;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
		neww->prev = tmp;
	}
}

void	tword_add_back(t_tlex **lst, t_word *neww)
{
	t_word	*tmp;

	if (!lst || !neww)
		return ;
	if (!(*lst)->cmd)
		(*lst)->cmd = neww;
	else
	{
		tmp = (*lst)->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neww;
	}
}

t_word	*tword_new(char *cmd, bool var, bool is_quoted)
{
	t_word	*p;

	p = calloc(1, sizeof(t_cmd));
	if (!p)
		crash_exit();
	p->str = cmd;
	p->is_var = var;
	p->is_quoted = is_quoted;
	p->next = NULL;
	return (p);
}
