/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:24:15 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 19:45:51 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 ** INCLUDES
 */
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

/*
 ** DEFINES
 */
# define APPEND		1
# define ARG		2
# define BUILTIN	3
# define COMMAND	4
# define DELIMITER	5
# define D_QUOTE	6
# define DIR_TYPE	7
# define ENV_TYPE	8
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

# ifdef __APPLE__
#  define OS_APPLE 1
# else
#  define OS_APPLE 0
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
typedef struct s_lst
{
	struct s_lst	*next;
	struct s_lst	*prev;
	char			*content;
	int				id;
}	t_lst;

typedef struct s_exe
{
	int		a[2];
	int		b[2];
	int		pip_cnt;
	int		redir_in;
	int		redir_out;
	char	**cmd_arg;
	int		flag_b;
	int		heredoc_fd[2];
	char	*heredoc_buf;
	pid_t	heredoc_pid;
	int		heredoc_status;
}	t_exe;

typedef struct s_data
{
	t_lst			*env_lst;
	t_lst			*exp_lst;
	unsigned char	exit_status;
	int				exit;
}	t_data;

t_data		g_data;

/*
 ** FUNCTIONS
 */
void	set_signal(void);
void	clear_screen(void);

int		tokenizer(t_lst **line_lst, char *line);
int		parse_1(t_lst **line_lst, char *line, int i);
int		check_1(t_lst *line_lst);
int		parse_2(t_lst *line_lst);
void	check_file_dir_delimiter_pip(t_lst *line_lst);
void	parse_3(t_lst *line_lst);
char	*dallor_str(char *s, int *idx);
char	*remain_str(char *s, int *idx);

int		check_id(int id);
int		is_builtin(char *str);
char	*exist_env(char *s);

void	syntax_error(char *err);
void	token_error(char *err, char token);
void	syntax_error_msg(char *err, char *msg);
void	syntax_error_msg2(char *err1, char *err2, char *msg);

void	connect_pipe(int fd[], int io);
void	close_pipe(int fd[]);
int		pipe_count(t_lst *line_lst);

int		redirect_in(char *file, t_exe *exe);
int		redirect_out(char *file, t_exe *exe);
int		redirect_append(char *file, t_exe *exe);
void	heredoc(t_lst *line_lst, t_exe *exe);
void	redirect_connect(t_lst *line_lst, t_exe *exe);

int		execute(t_lst *line_lst);
t_exe	*init_exe(t_lst *line_lst);
void	child_process(t_lst *line_lst, t_exe *exe, int i);
void	exe_builtin(t_exe *exe);
void	exe_command(t_exe *exe);
void	parent_process(t_exe *exe, pid_t pid, int i);
void	command_arg(t_lst **line_lst, t_exe *exe);

/*
 * utils
 */
t_lst	*pp_lstnew(char *content, int id);
t_lst	*pp_lstlast(t_lst *lst);
void	pp_lstadd_back(t_lst **lst, t_lst *new);
void	pp_lstadd_front(t_lst **lst, t_lst *new);
void	pp_lstdelone(t_lst *lst);
int		pp_lstsize(t_lst *lst);

int		pp_strcmp_limit(const char *s1, const char *s2, char limit);

void	find_executable(char *command, char *envs[], char buffer[], \
		int buf_size);

void	free_list(t_lst *lst);
void	exe_free(t_exe *exe);
int		free_args(char **args);
void	free_linelst_and_line(t_lst **line_lst, char **line);
void	free_tmp(char *tmp[4], int init);

/*
 * builtins
 */
int		pp_echo(char **args);
int		pp_cd(char **args);
int		pp_env(t_lst **env_lst);
int		pp_export(char *args, t_lst **exp_lst, t_lst **env_lst);
int		pp_pwd(void);
int		pp_unset(char *args, t_lst **exp_lst, t_lst **env_lst);

int		env_list(char **env);
void	put_env_index(void);

int		exp_list(void);

long	check_exit_num(const char *str);
void	exit_arg(t_lst **line_lst);

char	*get_key(char *str);
char	*get_value(char *str);
int		is_exist_eq(char *s);
t_lst	*is_same_content_key(t_lst **lst, char *key);

char	*key_eq_val(char *key, char *val);
void	change_env_val(t_lst *lst, char *val);
int		add_env(t_lst **env_lst, char *str);

char	*str_eq_quote_val(char *key, char *val);
void	change_exp_val(t_lst *lst, char *val);
int		add_exp(t_lst **exp_lst, char *str);

// test.c
void	print_lst(t_lst *lst);
void	print_line_list(t_lst *line_lst);
void	print_exe_cmdarg(t_exe *exe);

#endif
