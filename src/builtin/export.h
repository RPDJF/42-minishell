/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:24:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:24:31 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../minishell.h"
# include "../env/env.h"

// ERROR MESSAGES
# define NOT_VALID_IDENTIFIER "not a valid identifier"

//	export: builtin export command
int		export_ms(int argc, char **argv);
char	*var_name(char *str);

#endif
