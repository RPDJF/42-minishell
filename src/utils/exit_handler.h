#ifndef EXIT_HANDLER_H
# define EXIT_HANDLER_H

# include "../minishell.h"
# include "../utils/colors.h"

//	crash_exit: exit the program when unexpected error
void	crash_exit(void);
//	error_exit: exit the program when expected error with specific message
void	error_exit(char **context, char *msg, int exitcode);
//	error_msg: sends specific error to the terminal without exiting
void	error_msg(char **context, char *msg);

#endif