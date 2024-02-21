/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:01:34 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/21 18:40:43 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int id, t_type type, void *s_class, t_token *prev)
{
	t_token	*token;

	token = galloc(sizeof(t_token));
	if (!token)
		return (0);
	token->id = id;
	token->type = type;
	token->prev = prev;
	if (prev)
		prev->next = token;
	token->next = 0;
	token->s_class = s_class;
	return (token);
}

t_token	*generate_fake_token(char **args, char **args2)
{
	t_cmd	*cmd[2];
	t_redir	*redir;
	t_token *token[3];

	cmd[0] = new_cmd(0, "echo", args);
	cmd[1] = new_cmd(1, "wc", args2);
	redir = new_redir("|");
	cmd[0]->fd_in = STDIN_FILENO;
	cmd[0]->fd_out = redir->fd[1];
	cmd[1]->fd_in = redir->fd[0];
	cmd[1]->fd_out = STDOUT_FILENO;
	token[0] = 0;
	token[0] = new_token(0, TYPE_CMD, cmd[0], 0);
	token[1] = new_token(1, TYPE_REDIR, redir, token[0]);
	token[2] = new_token(2, TYPE_CMD, cmd[1], token[1]);
	return (token[0]);
}

void	pipe_exec(t_token *token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)token->s_class;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		printf("\n\naller\n\n");
		if (cmd->fd_in != STDIN_FILENO)
		{
			printf("ah!\n");
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			printf("béh!\n");
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		execv(cmd->args[0], cmd->args);
		printf("%p\n", cmd->args);
		printf("[ATTENTION] %s\t-%s\neeh..\n", cmd->content, cmd->args[0]);
		exit(0);
		return ;
	}
	else if (cmd->pid < 0)
		exit(1);
	else
	{
		waitpid(cmd->pid, 0, 0);
	}
}

void	process(t_token *token)
{
	while (token)
	{
		printf("token: %p\n", token);
		printf("token 2: %p\n", token->next);
		if (token->type == TYPE_CMD)
			pipe_exec(token);
		if (token->type == TYPE_REDIR)
		{
			printf("oof\n");
			close(((t_redir *)token->s_class)->fd[1]);
		}
		token = token->next;
	}
}

int	main(void)
{
	t_token *token;
	char	*args[] = {
		"/bin/echo",
		"Salut hello",
		" ",
		"tonton !",
		0,
	};
	char	*args2[] = {
		"/usr/bin/wc",
		0,
	};

	token = generate_fake_token(args, args2);
	process(token);
	exit (0);
}
