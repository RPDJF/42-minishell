/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:26:05 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:26:05 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../minishell.h"
# include <readline/readline.h>
# include "history.h"
# include "../executor/executor.h"

//	here_doc:	function that reads from stdin until a delimiter is found
//	delimiter:	the string that will be used to stop reading
//	is_quoted:	if the delimiter is quoted
//	return:	fd of a pipe that contains the input read
int	here_doc(char *delimiter, bool is_quoted);

#endif