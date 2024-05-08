/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:23:56 by rude-jes          #+#    #+#             */
/*   Updated: 2024/05/08 16:23:58 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "cd.h"
# include "echo.h"
# include "envb.h"
# include "exit.h"
# include "pwd.h"
# include "export.h"
# include "unset.h"

int	builtin_exec(char *builtin, int argc, char **argv, bool is_piped);

#endif