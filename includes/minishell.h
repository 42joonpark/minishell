/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:39:41 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/03 19:24:15 by donpark          ###   ########.fr       */
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
# include <limits.h>
# include <dirent.h>	// opendir
# include "libft.h"

/*
 ** DEFINES
 */
# define APPEND		1
# define ARG		2
# define BUILTIN	3	// builtin 함수(명령어)
# define COMMAND	4	// which 로 실행할 수 있는 애들
# define DELIMITER	5
# define D_QUOTE	6
# define DIR_TYPE	7
# define ENV_TYPE	8	// $
# define FILE_TYPE	9
# define S_QUOTE	10
# define HEREDOC	11
# define PIP		12
# define REDIROUT	13
# define REDIRIN	14

# define TRUE	1
# define FALSE	0
# define WHICH_DIR	"/usr/bin/which"
# define READ	0
# define WRITE	1

# ifndef P_BUFFER_SIZE
#  define P_BUFFER_SIZE 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 65536
# endif

# define C_NC		"\033[0m"
# define C_BLOCK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_YELLOW	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_PURPLE	"\033[35m"
# define C_AQUA		"\033[36m"

/*
 ** TYPEDEFS
 */
typedef struct s_command{
	char			*name;
	int				(*func)(char **args);
	char			*doc;
}					t_command;

typedef struct s_lst
{
	struct s_lst	*next;
	struct s_lst	*prev;
	char			*content;
	int				id;
}	t_lst;

typedef struct s_data
{
	char	**env;
	char	exit_status;	// 종료코드에는 1byte가 사용되면 0~255 번을 사용가능하다.
	// int		a[2];
	// int		b[2];
	// int		pip_cnt;
	// int		cmd_cnt;
	// char	*cmd_arg;

	// int		curr_cmd;
}	t_data;

t_data		g_data;

/*
 ** FUNCTIONS
 */
void	clear_screen(void);
void	find_executable(char *command, char *envs[], char buffer[],
			int buf_size);

void	free_list(t_lst *lst);

void	syntax_error(char *err);

int		pp_pwd(void);
int		pp_echo(char **args);
int		pp_cd(char **args);

// env
int		env_list(t_lst **env_lst, char **env);
void	put_env_index(t_lst **env_lst);
int		pp_env(t_lst **env_lst);

// export
int		exp_list(t_lst **exp_lst, t_lst **env_lst);
int		pp_export(char **args, t_lst **exp_lst, t_lst **env_lst);

char	*key_eq_val(char *key, char *val);
void	change_env_val(t_lst *lst, char *val);
int		add_env(t_lst **env_lst, char *str);

char	*str_eq_quote_val(char *key, char *val);
void	change_exp_val(t_lst *lst, char *val);
int		add_exp(t_lst **exp_lst, char *str);

char	*get_key(char *str);
char	*get_value(char *str);
int		is_exist_eq(char *s);
t_lst	*is_same_content_key(t_lst **lst, char *key);

// unset
int		pp_unset(char **args, t_lst **exp_lst, t_lst **env_lst);


int		is_builtin(char *str);
int		modify_arg_type(t_lst *line_lst);
int		parse_line(t_lst **line_lst, char *line);
void	check_dollar(t_lst *line_lst, t_lst *env_lst);
void	execute(t_lst **line_lst);

// main
int		minishell_loop(t_lst **env_lst, t_lst **exp_lst);

// utils
char	**pp_split(char *s, char c);
size_t	pp_strlen(const char *s);
int		pp_strcmp(const char *s1, const char *s2);
int		pp_strcmp_limit(const char *s1, const char *s2, char limit);
int		free_args(char **args);

void	*pp_memset(void *b, int c, size_t len);
char	*pp_strdup(const char *s1);
size_t	pp_strlcpy(char *dst, const char *src, size_t dstsize);
char	*pp_strjoin(char const *s1, char const *s2);
char	*pp_substr(char const *s, unsigned int start, size_t len);

t_lst	*pp_lstnew(char *content, int id);
t_lst	*pp_lstlast(t_lst *lst);
void	pp_lstadd_back(t_lst **lst, t_lst *new);
void	pp_lstadd_front(t_lst **lst, t_lst *new);
void	pp_lstdelone(t_lst *lst);
int		pp_lstsize(t_lst *lst);

int		get_next_line(int fd, char **line);
int		is_cut_idx(char *str, int *cut_idx);


// test
void	print_line_list(t_lst *line_lst);
void	print_lst(t_lst *lst);
#endif
