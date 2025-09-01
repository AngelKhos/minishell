/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:09:19 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/30 14:44:22 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <signal.h>
#include <readline/readline.h>

void	sigint_handle(int code)
{
	(void)code;
	if (g_pid == 0)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal(void)
{
	signal(SIGINT, &sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}
