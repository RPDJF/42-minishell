#ifndef BUILTIN_H
# define BUILTIN_H

# include "cd.h"
# include "echo.h"
# include "exit.h"
# include "pwd.h"
# include "export.h"
# include "unset.h"

int	builtin_exec(char *builtin, int argc, char **argv, bool is_piped);

#endif