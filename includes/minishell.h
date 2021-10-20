#ifndef MINISHELL_H
# define MINISHELL_H

/*
 ** INCLUDES
 */
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>

/*
 ** DEFINES
 */
# define	TRUE	1
# define	FALSE	0

/*
 ** TYPEDEFS
 */
typedef struct s_command
{
	char	*name;					/* User printable name of the function. */
	int		(*func)(char **args);	/* Function to call to do the job. */
	char	*doc;					/* Documentation for this function. */
}	t_command;

/*
 ** FUNCTIONS
 */
void	clear_screen(void);
char	**pp_split(char const *s, char c);

#endif
