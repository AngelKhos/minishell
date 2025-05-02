/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:00:31 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/02 16:39:03 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lizzardlib/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void	do_fork(char **cmd, char **env)
{
	(void)cmd;
	(void)env;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_printf("bonjour\n");
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	int	i;

	i = 0;
	while (i < 10) {
		do_fork(argv, env);
		wait(NULL);
		i++;
	}
}