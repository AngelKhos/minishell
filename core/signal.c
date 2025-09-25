/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:09:19 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/25 15:04:43 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <signal.h>
#include <readline/readline.h>

void	sigint_handle(int code)
{
	g_sig_val = code + 128;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exec_sigint_handle(int code)
{
	g_sig_val = code + 128;
	write(2, "\n", 1);
	rl_replace_line("", 0);
}

void	hd_sigint_handle(int code)
{
	g_sig_val = code + 128;
	rl_replace_line("", 0);
	rl_done = 1;
}

int	rl_hook_event_handler(void)
{
	if (g_sig_val == 130)
		rl_done = 1;
	return (0);
}

void	handle_signal(void)
{
	signal(SIGINT, &sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}
