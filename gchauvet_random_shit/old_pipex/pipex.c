#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	child_proc(char **argv, char **envp, int *pipes, int pid[2])
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		exit_error("open");
	pid[0] = fork();
	if (pid[0] == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		close(infile);
		exit_error("fork");
	}
	if (pid[0] == 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1
			|| dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), close(pipes[1]), close(pipes[0]), (void)0);
		close(pipes[0]);
		close(pipes[1]);
		close(infile);
		execute(argv[2], envp, infile);
	}
	close(infile);
}

void	child2_proc(char **argv, char **envp, int *pipes, int pid[2])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		exit_error("open");
	pid[1] = fork();
	if (pid[1] == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		close(outfile);
		exit_error("fork");
	}
	if (pid[1] == 0)
	{
		if (dup2(pipes[0], STDIN_FILENO) == -1
			|| dup2(outfile, STDOUT_FILENO) == -1)
			return (close(pipes[0]), close(outfile), close(pipes[1]), (void)0);
		close(pipes[1]);
		close(pipes[0]);
		close(outfile);
		execute(argv[3], envp, outfile);
	}
	close(outfile);
}

int	main(int argc, char **argv, char **envp)
{
	int	pid[2];
	int	help;
	int	pipes[2];

	if (!envp)
		return (EXIT_FAILURE);
	if (argc != 5)
		return (write(2, "Bad arguments\n", 15), EXIT_FAILURE);
	if (pipe(pipes) == -1)
		exit_error("pipe");
	child_proc(argv, envp, pipes, pid);
	child2_proc(argv, envp, pipes, pid);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], &help, 0);
	waitpid(pid[1], &help, 0);
	return (0);
}
