/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:39:41 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 19:55:51 by donpark          ###   ########.fr       */
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

typedef struct s_env
{
	char	*str;
	int		idx;
}	t_env;

/*
 ** FUNCTIONS
 */
void	clear_screen(void);
void	find_executable(char *command, char *envs[], char buffer[],
			int buf_size);
int		pp_pwd(char **args);
int		pp_echo(char **args);
int		pp_cd(char **args);
int		pp_env(char **env);

int		env_list_alloc(char **env, int *env_cnt, t_env **env_list);
int		save_env_data(char **env, int env_cnt, t_env *env_list);
void	print_sorted_env(int env_cnt, t_env *env_list);
int		pp_export(char **args, int env_cnt, t_env *env_list);
void	minishell_loop();

/*
 ** UTILS
 */
char	**pp_split(char *s, char c);
size_t	pp_strlen(const char *s);
int		pp_strcmp(const char *s1, const char *s2);
int		pp_strcmp_limit(const char *s1, const char *s2, char limit);
int		free_args(char **args);

#endif
