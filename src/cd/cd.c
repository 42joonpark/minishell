/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:23:36 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:23:37 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void add_oldpwd(void)
{
	char    *tmp;
	char    *pwd;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", pwd);
	pp_export(tmp, &g_data.exp_lst, &g_data.env_lst);
	free(pwd);
	free(tmp);
}

static char *oldpwd_get_value(char *oldpwd)
{
	t_lst   *lst;
	char    *key;

	lst = g_data.env_lst;
	while (lst != NULL)
	{
		key = get_key(lst->content);
		if (ft_strcmp(oldpwd, key) == 0)
		{
			free(key);
			return (get_value(lst->content));
		}
		free(key);
		lst = lst->next;
	}
	return (NULL);
}

static int  return_result(int flag, char *dir)
{
	if (flag)
		free(dir);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}

static int  do_cd(char **args, char *dir, int flag)
{
	add_oldpwd();
	if (chdir(dir) == -1)
	{
		syntax_error_msg2("cd", args[1], "No such file or directory");
		g_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (return_result(flag, dir));
}

int pp_cd(char **args)
{
	char    *default_dir;
	char    *dir;
	int     flag;

	flag = FALSE;
	default_dir = getenv("HOME");
	if (args[1] == NULL)
		dir = default_dir;
	else if (args[1][0] == '~')
	{
		dir = ft_strjoin(default_dir, &args[1][1]);
		flag = TRUE;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		dir = oldpwd_get_value("OLDPWD");
		flag = TRUE;
	}
	else
		dir = args[1];
	return (do_cd(args, dir, flag));
}