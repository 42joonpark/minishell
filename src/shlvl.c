/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:07:47 by donpark           #+#    #+#             */
/*   Updated: 2021/11/18 14:09:06 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shlvl(void)
{
	char	*val;
	t_lst	*shlvl_lst;
	char	*tmp;

	shlvl_lst = is_same_content_key(&g_data.env_lst, "SHLVL");
	val = get_value(shlvl_lst->content);
	g_data.shlvl = ft_atoi(val) + 1;
	free(val);
	val = ft_itoa(g_data.shlvl);
	tmp = ft_strjoin("SHLVL=", val);
	free(val);
	pp_export(tmp, &g_data.exp_lst, &g_data.env_lst);
	free(tmp);
}
