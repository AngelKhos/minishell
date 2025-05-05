/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:00:31 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:05 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lizzardlib/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "turbo_pipex.h"


void	do_fork(char **cmd, char **env, int index)
{
	(void)cmd;
	(void)env;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execute(cmd[index], env, 12);
		ft_printf("bonjour\n");
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	while (i < argc - 1) {
		do_fork(argv, env, i);
		wait(NULL);
		i++;
	}
}