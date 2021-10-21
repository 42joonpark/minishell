/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:23:49 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 18:18:39 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
size_t	pp_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	pp_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[i] || p2[i])
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
*/
int	pp_pwd(char **args)
{
	char	*pwd;

	if (pp_strcmp(args[0], "pwd"))
		return (0);
	pwd = getcwd(NULL, 0);
	write(1, pwd, pp_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (1);
}

/*
int	main(void)
{
	int	ret;
	char	*args[] = {"pwd",};

	ret = pp_pwd(args);
	if (ret == 1)
		printf("cmd is not \'pwd\'\n");
	else
		printf("cmd is \'pwd\'\n");
	return (0);
}
*/
