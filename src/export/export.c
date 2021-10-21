/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:23:29 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 17:03:41 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char	*str;
	int		idx;
}	t_env;

static int	env_list_alloc(char **env, int *env_cnt, t_env **env_list)
{
	*env_cnt = 0;
	while (env[*env_cnt])
		(*env_cnt)++;
	*env_list = (t_env *)malloc(sizeof(t_env) * (*env_cnt));
	if (*env_list == NULL)
		return (0);
	return (1);
}

static void	print_env(int env_cnt, t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < env_cnt)
	{
		if (e[i].idx == j)
		{
			write(1, e[i].str, pp_strlen(e[i].str));
			write(1, "\n", 1);
			j++;
			i = -1;
		}
		i++;
	}

}

int	env_sort(char **env)
{
	int	env_cnt;
	int	i;
	int	j;
	int	idx;
	t_env *env_list;

	env_list_alloc(env, &env_cnt, &env_list);
	i = -1;
	while (env[++i])
	{
		idx = 0;
		j = -1;
		while (env[++j])
		{
			if (pp_strcmp_limit(env[i], env[j], '=') > 0)
				idx++;
		}
		env_list[i].str = env[i];
		env_list[i].idx = idx;
	}
	print_env(env_cnt, env_list);
	free(env_list);
	return (0);
}


int	pp_export(char **args, char **env)
{
	if (pp_strcmp(args[0], "export") == 0 && args[1] == NULL)
		env_sort(env);
	return (1);
}
