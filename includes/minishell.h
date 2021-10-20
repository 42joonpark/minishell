/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:39:41 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 15:42:04 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define WHICH_DIR	"/usr/bin/which"

/*
 ** TYPEDEFS
 */
typedef struct s_command{
	char			*name;
	int				(*func)(char **args);
	char			*doc;
}					t_command;

/*
 ** FUNCTIONS
 */
void	clear_screen(void);
char	**pp_split(char *s, char c);
void	find_executable(char *command, char *envs[], char buffer[],
			int buf_size);

#endif 
