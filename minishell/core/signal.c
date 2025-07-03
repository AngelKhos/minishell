/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:09:19 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/03 15:57:37 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

void	sigint_handle()
{
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigabrt_handle()
{
	ft_printf("abort\n");
}

void	sigsegv_handle()
{
	ft_printf("Segmentation fault\n");
	exit(EXIT_FAILURE);
}

void	handle_signal()
{
	signal(SIGINT, &sigint_handle);
	signal(SIGSEGV, &sigsegv_handle);
	signal(SIGABRT, &sigabrt_handle);
	signal(SIGQUIT, SIG_IGN);
}