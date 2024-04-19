#ifndef EXIT_HANDLER_H
# define EXIT_HANDLER_H

# include "../minishell.h"
# include "../utils/colors.h"
# include <readline/readline.h>

//	Error codes
//		Error messages
# define IS_DIR "is a directory"
# define COMMAND_NOT_FOUND "command not found"

//	secure_exit: exits the program with a specific exit code freeing all memory
void	secure_exit(int exitcode);
//	crash_exit: exit the program when unexpected error
void	crash_exit(void);
//	error_exit: exit the program when expected error with specific message
void	error_exit(char **context, char *msg, int exitcode);
//	error_msg: sends specific error to the terminal without exiting
void	error_msg(char **context, char *msg);
//	error_cmd: sends specific error to the terminal and exits
void	error_cmd(char *path);

#endif