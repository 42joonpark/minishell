/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:28:13 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 18:28:14 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	var_add_env(t_lst **env_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_lst	*tmp;
	int		flag;

	flag = FALSE;
	if (is_exist_eq(exp_var))
	{
		str = key_eq_val(key, val);
		flag = TRUE;
	}
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
	if (flag == TRUE)
		free(str);
}

static void	var_add_exp(t_lst **exp_lst, char *exp_var, char *key, char *val)
{
	char	*str;
	t_lst	*tmp;
	int		flag;

	flag = FALSE;
	if (is_exist_eq(exp_var))
	{
		str = str_eq_quote_val(key, val);
		flag = TRUE;
	}
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
	if (flag == TRUE)
		free(str);
}

int	pp_export(char *args, t_lst **exp_lst, t_lst **env_lst)
{
	char	*key;
	char	*val;

	if (env_lst == NULL || exp_lst == NULL)
	{
		g_data.exit_status = 126;
		return (EXIT_FAILURE);
	}
	if (args == NULL)
		print_exp_lst(*exp_lst);
	else
	{
		key = get_key(args);
		val = get_value(args);
		var_add_env(env_lst, args, key, val);
		var_add_exp(exp_lst, args, key, val);
		free(key);
		free(val);
	}
	return (EXIT_SUCCESS);
}
