#ifndef TYPES_H
# define TYPES_H

# define APPEND		1
# define ARG		2
# define BUILTIN	3 // builtin 함수(명령어)
# define COMMAND	4 // which 로 실행할 수 있는 애들
# define D_QUOTE	5
# define DIR_TYPE	6
# define ENV_TYPE	7
# define FILE_TYPE	8
# define S_QUOTE	9
# define HEREDOC	10
# define PIP		11
# define REDIROUT	12
# define REDIRIN	13

/*
typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	int				init_sort_idx;
}	t_list;
*/


#endif
