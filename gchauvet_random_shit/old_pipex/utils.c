#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

char	*find_loop(char	**paths, char	*path_no_cmd, char *cmd)
{
	char	*path;
	size_t	i;

	path = NULL;
	i = 0;
	while (paths[i])
	{
		path_no_cmd = ft_strjoin(paths[i], "/");
		if (!path_no_cmd)
			return (freearray(paths), free(path), NULL);
		if (path)
			free(path);
		path = ft_strjoin(path_no_cmd, cmd);
		if (!path)
			return (free(path_no_cmd), freearray(paths), NULL);
		free(path_no_cmd);
		if (access(path, X_OK) == 0)
			return (freearray(paths), path);
		i++;
	}
	write(2, "invalid command\n", 15);
	return (freearray(paths), free(path), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_no_cmd;
	size_t	i;

	path_no_cmd = NULL;
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_loop(paths, path_no_cmd, cmd));
}

int	execute(char *cmd_arg, char **envp, int file)
{
	char	*path;
	char	**cmd;

	cmd = NULL;
	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		return (close(file), 0);
	path = find_path(cmd[0], envp);
	if (!path)
		return (freearray(cmd), close(file), 0);
	if (execve(path, cmd, envp) == -1)
	{
		freearray(cmd);
		free(path);
		close(file);
		exit_error("execve");
	}
	return (0);
}

void	freearray(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	exit_error(char *error)
{
	perror(error);
	exit(0);
}
