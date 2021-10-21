/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:23:29 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 19:48:25 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_alloc(char **env, int *env_cnt, t_env **env_list)
{
	*env_cnt = 0;
	while (env[*env_cnt])
		(*env_cnt)++;
	(*env_cnt)--;
	*env_list = (t_env *)malloc(sizeof(t_env) * (*env_cnt));
	if (*env_list == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	print_sorted_env(int env_cnt, t_env *env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < env_cnt)
	{
		if (env_list[i].idx == j)
		{
			write(1, env_list[i].str, pp_strlen(env_list[i].str));
			write(1, "\n", 1);
			j++;
			i = -1;
		}
		i++;
	}
}

int	save_env_data(char **env, int env_cnt, t_env *env_list)
{
	int	i;
	int	j;
	int	sorted_idx;

	i = 0;
	while (i < env_cnt)
	{
		sorted_idx = 0;
		j = 0;
		while (j < env_cnt)
		{
			/**
			 *  양수라면 env[i]가 env[j]보다 더 크고 정렬상 뒤에 와야 한다.
			 *  자기자신을 포함한 모든 env 의 키값을 자신과 비교해서
			 *  만약에 자기자신의 값이 비교하려는 값(env[j])보다 크다면 뒤로가야하니 정렬 index를 증가 시켜주겠다.
			 */
			if (pp_strcmp_limit(env[i], env[j], '=') > 0)
				sorted_idx++;
			j++;
		}
		env_list[i].str = env[i];
		env_list[i].idx = sorted_idx;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	pp_export(char **args, int env_cnt, t_env *env_list)
{
	if (pp_strcmp(args[0], "export") == 0 && args[1] == NULL)
		print_sorted_env(env_cnt, env_list);
	return (EXIT_SUCCESS);
}
