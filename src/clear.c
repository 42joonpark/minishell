/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:43:03 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 11:36:18 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_screen(void)
{
	static const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
