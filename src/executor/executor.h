/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:25:44 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/09 15:53:52 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include "../builtin/builtin.h"
# include "../expand/expand_words.h"
# include "../utils/binary_finder.h"
# include "../prompter/here_doc.h"
# include "../signals/signals.h"

typedef struct s_context	t_context;
typedef struct s_context
{
	t_context	*next;
	t_context	*prev;
	bool		*has_pipe;
	int			*og_fd_in;
	int			*og_fd_out;
	int			fd_in;
	char		*fd_in_path;
	int			fd_out;
	char		*fd_out_path;
	char		*err_fd;
}	t_context;

typedef struct s_executor
{
	bool		has_pipe;
	t_token		*tokens;
	int			og_fd_in;
	int			og_fd_out;
	t_context	*context;
}	t_executor;

//	executor:	execute a list of tokens inside minishell
int			executor(t_token *tokens);
//	get_exitcode:	get the exit code of the last process
int			get_exitcode(void);
//	init_child:	init and execute a child from cmd or builtin token
pid_t		init_child(t_token *tokens);
//	exec_pipe:	handles pipe type tokens
void		exec_pipe(t_context *context, t_token *tokens);
//	exec_redir:	handles redirections type tokens
void		exec_redir(t_context *context, t_token *tokens);
//	exec_here_doc:	handles stdin here_doc type tokens
void		exec_here_doc(t_context *context, t_token *tokens);
//	wait_all_tokens:	wait for tokens to finish executing
//	returns last process exit code
int			wait_all_tokens(t_token *tokens);
//	wait_token:	wait for a token to finish executing
int			wait_token(t_token *token);
//	has_pipe:	check if a token list has a pipe token
bool		has_pipe(t_token *tokens);
//	dup_fd:	duplicate file descriptors to STDIN_FILENO and STDOUT_FILENO
int			dup_fd(t_context *context);
//	exit_signint:	exit all processes killing them with SIGINT
void		exit_signint(t_executor *executor, int _sigint);
//	exec_var_init:	initialize local variables for execution
void		exec_var_init(t_executor *executor, t_token *tokens);
//	is_builtin:	check if a command is a builtin
bool		is_builtin(t_cmd *cmd);
//	find_cmd:	find a command in the *cmd;
t_cmd		*find_cmd(t_cmd *cmd);
//	close_all_fd:	close all file descriptors in context
void		close_all_fd(t_context *context);
//	init_executor:	initialize executor struct
t_context	*init_context(t_executor *executor);
//	find_last_cmd:	find the last command in the executor
t_token		*find_last_cmd(t_executor *exec, t_token *token);
//	init_subshell:	initialize and execute a subshell
pid_t		init_subshell(t_token *tokens);
//	parse_cmd_var:	parse command if is variable call
t_word		**parse_cmd_var(t_cmd *cmd);

#endif