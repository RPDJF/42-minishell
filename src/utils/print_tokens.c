/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilyanar <ilyanar@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:58:07 by ilyanar           #+#    #+#             */
/*   Updated: 2024/04/29 16:00:05 by ilyanar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
//
// void	print_tokens(t_token *tokens)
// {
// 	char	*token_type;
//
// 	while (tokens)
// 	{
// 		printf("\ntoken %p\n", tokens);
// 		if (tokens->type == token_cmd)
// 			token_type = "token_cmd";
// 		else if (tokens->type == token_var)
// 			token_type = "token_var";
// 		else if (tokens->type == token_pipe)
// 			token_type = "token_pipe";
// 		else if (tokens->type == token_stdin)
// 			token_type = "token_stdin";
// 		else if (tokens->type == token_stdout)
// 			token_type = "token_stdout";
// 		else if (tokens->type == token_and)
// 			token_type = "token_and";
// 		else if (tokens->type == token_or)
// 			token_type = "token_or";
// 		else if (tokens->type == token_subshell)
// 			token_type = "token_subshell";
// 		printf("type: %s\n", token_type);
// 		printf("next: %p\n", tokens->next);
// 		if (tokens->type == token_cmd)
// 		{
// 			t_cmd	*cmd = (t_cmd *)tokens->data;
// 			printf("cmd: ");
// 			t_word	*tmp = cmd->cmd;
// 			while (tmp)
// 			{
// 				printf("%s", tmp->str);
// 				tmp = tmp->next;
// 			}
// 			printf("\n");
// 			printf("argv: ");
// 			for (int i = 0; cmd->argv[i]; i++)
// 				printf("\"%s\", ", cmd->argv[i]->str);
// 		}
// 		else if (tokens->type == token_stdout)
// 		{
// 			t_stdout	*cmd = (t_stdout *)tokens->data;
// 			printf("is_append: %d\n", cmd->is_append);
// 			printf("filename: %s", cmd->filename->str);
// 		}
// 		else if (tokens->type == token_subshell)
// 			print_tokens(((t_subshell *)(tokens)->data)->token);
// 		printf("\n\n[end token]\n\n\n");
// 		tokens = tokens->next;
// 	}
// }
//
// void	print_lex(t_tlex *lex)
// {
// 	int		i;
// 	t_word	*tmp2;
//
// 	i = 0;
// 	if (lex)
// 	{
// 		for (t_tlex *tmp1 = lex; tmp1; tmp1 = tmp1->next)
// 		{
// 			ft_printf("noeud[%d]", i);
// 			tmp2 = tmp1->cmd;
// 			while (tmp2)
// 			{
// 				ft_printf("--->[%s:%d:%d]", tmp2->str,
// 					tmp2->is_var, tmp2->is_quoted);
// 				tmp2 = tmp2->next;
// 			}
// 			i++;
// 			ft_printf("\n");
// 		}
// 	}
// }
