/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:23:29 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/25 14:40:40 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exp_lst(t_list *lst)
{
	while (lst != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, lst->content, pp_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
}

/**
 * = 이 있는지 확인, = 없으면 env_lst에 추가하지 않음
 * key=val 문자열 만듦
 * = 이 없고, val이 없는 상태가 아니라면 ex) 'export a'와 같은 경우가 아니라면
 * lst->content 의 key와 같은 lst 가져오기
 */
static void	var_add_env(t_list **env_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_list	*tmp;

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

static void	var_add_exp(t_list **exp_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_list	*tmp;

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

/**
 * need free : key, val, lst->content, lst
 */
int	pp_export(char **args, t_list **exp_lst, t_list **env_lst)
{
	char	*key;
	char	*val;

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
