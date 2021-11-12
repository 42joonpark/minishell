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
# include <dirent.h>	// opendir
# include <string.h>
# include <errno.h>
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

typedef struct	s_exe
<<<<<<< HEAD
{
	int		a[2];
	int		b[2];
	int		pip_cnt;
	int		redir_in;
	int		redir_out;
	char	**cmd_arg;
}	t_exe;

typedef struct s_termios
=======
>>>>>>> 67054cfc524e86d5ff79a535fd4ce1fe0e82aeef
{
	int		a[2];
	int		b[2];
	int		pip_cnt;
	int		redir_in;
	int		redir_out;
	char	**cmd_arg;
	int		flag_b;
}	t_exe;

typedef struct s_data
{
	t_lst	*env_lst;
	t_lst	*exp_lst;
	char	exit_status;	// 종료코드에는 1byte가 사용되면 0~255 번을 사용가능하다.
}	t_data;

t_data		g_data;

/*
 ** FUNCTIONS
 */
// clear_screen.c
void	clear_screen(void);

// env/env_list.c
int		env_list(char **env);
void	put_env_index(void);

// export/export_list.c
int		exp_list(void);

// tokenizer.c
int		tokenizer(t_lst **line_lst, char *line);
int		parse_1(t_lst **line_lst, char *line);
int		check_1(t_lst *line_lst);
int		parse_2(t_lst *line_lst);
void	parse_3(t_lst *line_lst);

// parse_util.c
int		check_id(int id);
int		is_builtin(char *str);

// error.c
void	syntax_error(char *err);
void	syntax_error_msg(char *err, char *msg);

// export/export_utils.c
char	*get_key(char *str);
char	*get_value(char *str);

// utils/pp_lst.c
t_lst	*pp_lstnew(char *content, int id);
t_lst	*pp_lstlast(t_lst *lst);
void	pp_lstadd_back(t_lst **lst, t_lst *new);
void	pp_lstadd_front(t_lst **lst, t_lst *new);
void	pp_lstdelone(t_lst *lst);
int		pp_lstsize(t_lst *lst);

// utils/pp_strcmp_limit.c
int		pp_strcmp_limit(const char *s1, const char *s2, char limit);

// utils/pp_which.c
void	find_executable(char *command, char *envs[], char buffer[], \
		int buf_size);

// utils/free.c
void	free_list(t_lst *lst);

// echo
int		pp_echo(char **args);

// execute.c
int		execute(t_lst *line_lst);

// test.c
void	print_lst(t_lst *lst);
void	print_line_list(t_lst *line_lst);
void	print_exe_cmdarg(t_exe *exe);



int		execute(t_lst *line_lst, char *envs[]);
void	find_executable(char *command, char *envs[], char buffer[], int buf_size);

#endif
