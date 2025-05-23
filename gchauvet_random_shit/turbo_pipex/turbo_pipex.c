/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:00:31 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/09 17:23:09 by authomas         ###   ########.fr       */
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

char	*convert_file_to_str(int file)
{
	char	*str;
	char	*line;

	line = get_next_line(file)
	while (line)
	{
		ft_strjoin(str, line);
		free(line)
		line = get_next_line(file);
	}
	return (str);
}

void	here_doc(char *argv)
{
	char	*end_message = "fin";
	char	*here_doc_str;
	int	pipes[2];
	int	pid;
	int here_doc;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		here_doc = open(".tmp_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(here_doc, STDOUT_FILENO);
		here_doc_str = convert_file_to_str(here_doc);
		while (ft_strncmp(here_doc_str, end_message, ft_strlen(end_message)) == 0)
		{
			here_doc_str = convert_file_to_str(here_doc);
		}
	}
}

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
		close(pipes[1]);
		execute(argv, env);
		exit(0);
	}
	else
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int infile;
	int outfile;
	int	i;

	infile = open("infile.txt", O_RDONLY, 0777);
	dup2(infile, STDIN_FILENO);
	close(infile);
	if (ft_strncmp(argv[argc - 1], "here_doc", 8) == 0)
	{
	}
	i = 1;
	while (i < argc - 1) {
		do_fork(argv[i], env);
		i++;
	}
	outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute(argv[argc - 1], env);
}