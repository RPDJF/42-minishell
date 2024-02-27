/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:20:04 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/27 17:38:40 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astnode	*new_astnode(char **args, t_type type)
{
	t_astnode	*astnode;

	astnode = galloc(sizeof(t_astnode));
	if (!astnode || !args)
		return (0);
	astnode->l_node = 0;
	astnode->r_node = 0;
	astnode->args = args;
	astnode->type = type;
	return (astnode);
}

t_astnode	*generate_fake_as2t(void)
{
	t_astnode	*astnode;
	t_astnode	*tmp;
	t_astnode	*tmp2;
	t_astnode	*tmp3;
	t_astnode	*tmp4;
	t_astnode	*tmp5;
	t_astnode	*tmp6;
	t_astnode	*tmp7;
	t_astnode	*tmp8;
	t_astnode	*tmp9;
	t_astnode	*tmp10;
	t_astnode	*tmp11;
	t_astnode	*tmp12;
	t_astnode	*tmp13;
	t_astnode	*tmp14;
	t_astnode	*tmp15;

	astnode = new_astnode(ft_split("|", ' '), e_pipe);
	if (!astnode)
		return (0);
	tmp = new_astnode(ft_split("echo a", ' '), e_cmd);
	if (!tmp)
		return (0);
	astnode->l_node = tmp;
	tmp = new_astnode(ft_split("|", ' '), e_pipe);
	if (!tmp)
		return (0);
	astnode->r_node = tmp;
	tmp2 = new_astnode(ft_split("echo b", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->l_node = tmp2;
	tmp2 = new_astnode(ft_split("echo c", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->r_node = tmp2;
	return (astnode);
}

t_astnode	*generate_fake_ast(void)
{
	t_astnode	*astnode;
	t_astnode	*tmp;
	t_astnode	*tmp2;

	astnode = new_astnode(ft_split("|", ' '), e_pipe);
	if (!astnode)
		return (0);
	tmp = new_astnode(ft_split("echo a", ' '), e_cmd);
	if (!tmp)
		return (0);
	astnode->l_node = tmp;
	tmp = new_astnode(ft_split("|", ' '), e_pipe);
	if (!tmp)
		return (0);
	astnode->r_node = tmp;
	tmp2 = new_astnode(ft_split("echo b", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->l_node = tmp2;
	tmp2 = new_astnode(ft_split("echo c", ' '), e_cmd);
	if (!tmp2)
		return (0);
	tmp->r_node = tmp2;
	return (astnode);
}

void	print_ast2(t_astnode *astnode)
{
	int	i;

	if (astnode->l_node)
	{
		print_ast2(astnode->l_node);
		printf(" ");
	}
	i = 0;
	while (astnode->args[i])
	{
		printf("%s", astnode->args[i++]);
		if (astnode->args[i])
			printf(" ");
	}
	if (astnode->r_node)
	{
		printf(" ");
		print_ast2(astnode->r_node);
	}
}

void	print_ast(t_astnode *astnode)
{
	int	i;
	int	j;

	while (astnode)
	{
		i = -1;
		while (i++, astnode->l_node && astnode->l_node->args[i])
		{
			ft_putstr_fd(astnode->l_node->args[i], STDOUT_FILENO);
			if (astnode->l_node->args[i + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		j = -1;
		while (j++, astnode->args[j])
		{
			ft_putstr_fd(astnode->args[j], STDOUT_FILENO);
			if (astnode->args[j + 1])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		astnode = astnode->r_node;
	}
}

void	prompt(t_minishell *minishell)
{
	char	*strprompt;

	while (true)
	{
		if (minishell->hostname && getenv("USER"))
			strprompt = ft_strsjoin(7, "\e[1;35m", getenv("USER"), "@",
					minishell->hostname, "\e[0m:\e[1;36m",
					getcwd(0, 0), "\e[0m❥ ");
		else if (getenv("USER"))
			strprompt = ft_strsjoin(5, "\e[1;35m", getenv("USER"),
					"\e[0m:\e[1;36m", getcwd(0, 0), "\e[0m❥ ");
		else
			strprompt = ft_strsjoin(5, "\e[1;35m", "minishell-0.1",
					"\e[0m:\e[1;36m", getcwd(0, 0), "\e[0m❥ ");
		if (!strprompt)
			return ;
		add_history(readline(strprompt));
		free(strprompt);
	}
}

static char	*mini_gethostname(void)
{
	const char	hostname[] = "/etc/hostname";
	char		*output;
	char		*tmp;
	char		*line;
	int			fd;

	fd = open(hostname, O_RDONLY);
	if (fd < 0)
		return (0);
	line = ft_get_next_line(fd);
	output = ft_strdup("");
	while (line)
	{
		if (output)
			tmp = output;
		output = ft_strjoin(output, line);
		if (!output)
			return (0);
		if (tmp)
			free (tmp);
		free(line);
		line = ft_get_next_line(fd);
	}
	output[ft_strlen(output) - 1] = 0;
	return (output);
}

t_minishell	*minishell_init(void)
{
	t_minishell	*minishell;

	minishell = galloc(sizeof(t_minishell));
	if (!minishell)
		return (0);
	minishell->hostname = mini_gethostname();
	return (minishell);
}

int	main(void)
{
	t_minishell	*minishell;
	t_astnode	*ast;

	ast = generate_fake_ast();
	print_ast(ast);
	printf("\n");
	print_ast2(ast);
	printf("\n");
	minishell = minishell_init();
	prompt(minishell);
	exit (0);
}
