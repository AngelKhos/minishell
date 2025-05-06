/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:00:31 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/06 14:30:56 by gchauvet         ###   ########.fr       */
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


void	do_fork(char *argv, char **env)
{
	int	pipes[2];
	int	pid;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		execute(argv, env);
		exit(0);
	}
	else
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int infile;
	int outfile;
	int	i;

	infile = open("infile.txt", O_RDONLY, 0777);
	outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(infile, STDIN_FILENO);
	i = 1;
	while (i < argc - 1) {
		do_fork(argv[i], env);
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
	execute(argv[argc - 1], env);
}