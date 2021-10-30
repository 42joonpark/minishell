/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:39:41 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/30 18:16:43 by joonpark         ###   ########.fr       */
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

# ifdef __APPLE__
#  define OS 1
# else
#  define OS 0
# endif

/*
 ** TYPEDEFS
 */
typedef struct s_command{
	char			*name;
	int				(*func)(char **args);
	char			*doc;
}					t_command;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	int				id;
}	t_list;

/*
 ** FUNCTIONS
 */
void	clear_screen(void);
void	find_executable(char *command, char *envs[], char buffer[],
			int buf_size);
int		pp_pwd(void);
int		pp_echo(char **args);
int		pp_cd(char **args);

// env
int		env_list(t_list **env_lst, char **env);
void	put_env_index(t_list **env_lst);
int		pp_env(t_list **env_lst);

// export
int		exp_list(t_list **exp_lst, t_list **env_lst);
int		pp_export(char **args, t_list **exp_lst, t_list **env_lst);

char	*key_eq_val(char *key, char *val);
void	change_env_val(t_list *lst, char *val);
int		add_env(t_list **env_lst, char *str);

char	*str_eq_quote_val(char *key, char *val);
void	change_exp_val(t_list *lst, char *val);
int		add_exp(t_list **exp_lst, char *str);

char	*get_key(char *str);
char	*get_value(char *str);
int		is_exist_eq(char *s);
t_list	*is_same_content_key(t_list **lst, char *key);

// unset
int		pp_unset(char **args, t_list **exp_lst, t_list **env_lst);

// main
void	minishell_loop(t_list **env_lst, t_list **exp_lst);

/*
 ** UTILS
 */
char	**pp_split(char *s, char c);
size_t	pp_strlen(const char *s);
int		pp_strcmp(const char *s1, const char *s2);
int		pp_strcmp_limit(const char *s1, const char *s2, char limit);
int		free_args(char **args);

char	*pp_strdup(const char *s1);
size_t	pp_strlcpy(char *dst, const char *src, size_t dstsize);
char	*pp_strjoin(char const *s1, char const *s2);

void	*pp_memset(void *b, int c, size_t len);
t_list	*pp_lstnew(void *content);
t_list	*pp_lstlast(t_list *lst);
void	pp_lstadd_back(t_list **lst, t_list *new);
void	pp_lstadd_front(t_list **lst, t_list *new);
void	pp_lstdelone(t_list *lst);
int		pp_lstsize(t_list *lst);

#endif
