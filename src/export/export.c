#include "minishell.h"

static void	print_exp_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
}

/**
 * = 이 있는지 확인, = 없으면 env_lst에 추가하지 않음
 * key=val 문자열 만듦
 * = 이 없고, val이 없는 상태가 아니라면 ex) 'export a'와 같은 경우가 아니라면
 * lst->content 의 key와 같은 lst 가져오기
 */
static void	var_add_env(t_lst **env_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_lst	*tmp;

	if (is_exist_eq(exp_var))
		str = key_eq_val(key, val);
	else
		str = NULL;
	if (!(is_exist_eq(exp_var) == 0 && val == NULL))
	{
		tmp = is_same_content_key(env_lst, key);
		if (tmp != NULL)
			change_env_val(tmp, val);
		else
			add_env(env_lst, str);
	}
}

static void	var_add_exp(t_lst **exp_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_lst	*tmp;

	if (is_exist_eq(exp_var))
		str = str_eq_quote_val(key, val);
	else
		str = key;
	tmp = is_same_content_key(exp_lst, key);
	if (tmp != NULL)
	{
		if (is_exist_eq(exp_var) == 1)
			change_exp_val(tmp, val);
	}
	else
		add_exp(exp_lst, str);
}

/*
 * TODO
 * export key=value (추가하는거)
 * a = b 이런식일 떄 에러 메시지
 ******************************************
 * need free : key, val, lst->content, lst
 */
int	pp_export(char **args, t_lst **exp_lst, t_lst **env_lst)
{
	char	*key;
	char	*val;

	if (env_lst == NULL || exp_lst == NULL)
	{
		g_data.exit_status = 126;
		return (EXIT_FAILURE);
	}
	if (args[1] == NULL)
		print_exp_lst(*exp_lst);
	else
	{
		key = get_key(args[1]);
		val = get_value(args[1]);
		var_add_env(env_lst, args[1], key, val);
		var_add_exp(exp_lst, args[1], key, val);
	}
	return (EXIT_SUCCESS);
}
