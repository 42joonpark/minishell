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
 ** FUNCTIONS
 */
void	clear_screen(void);

#endif 
