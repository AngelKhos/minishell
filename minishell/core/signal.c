/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:09:19 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/28 10:57:11 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <signal.h>
#include <readline/readline.h>

void	sigint_handle()
{
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_pid == 0)
		rl_redisplay();
}

void	handle_signal()
{
	signal(SIGINT, &sigint_handle);
	signal(SIGQUIT, SIG_IGN);
}