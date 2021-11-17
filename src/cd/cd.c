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

static void add_oldpwd(int flag, char *dir)
{
    char    *tmp;
    char    *pwd;
    pwd = getcwd(NULL, 0);
    tmp = ft_strjoin("OLDPWD=", pwd);
    pp_export(tmp, &g_data.exp_lst, &g_data.env_lst);
    free(pwd);
    free(tmp);
    if (flag)
        free(dir);
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
    else
        dir = args[1];
    if (chdir(dir) == -1)
    {
        syntax_error_msg2("cd", args[1], "No such file or directory");
        g_data.exit_status = 1;
        return (EXIT_FAILURE);
    }
    add_oldpwd(flag, dir);
    g_data.exit_status = 0;
    return (EXIT_SUCCESS);
}