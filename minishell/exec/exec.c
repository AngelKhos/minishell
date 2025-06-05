/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/05 12:43:07 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <readline/readline.h>

char	*convert_part_to_arg(t_data *data, t_cmd *cmd, int index)
{
	int		size;
	int		i;
	char	*cmd_plus_arg;

	(void)data;
	cmd_plus_arg = NULL;
	i = 0;
	size = 1;
	while (cmd[0].parts[index+size].type == ARG) // ajoute une conditon pour repeperer les pipes | doc la fin d'une function
		size++;
	while (i < size)
	{
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, " ");
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, cmd[0].parts[i].str);
		i++;
	}
	ft_printf("cpta : %s\n", cmd_plus_arg);
	return (cmd_plus_arg);
}

void	exec_cmd_no_pipe(t_data *data, char *cmd_array)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		execute(cmd_array, data->envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	exec_cmd_with_pipe(t_data *data, char *cmd_array, int pipes[2])
{
	int		pid;
	
	pid = fork();
	if (pid == 0)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
		execute(cmd_array, data->envp);
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

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int		nb_arg;
	int		cmd_index;
	char	*cmd_array;
	int		pipes[2];

	cmd_index = 0;
	nb_arg = 0;
	if (data->nb_pipes <= 0)
	{
		cmd_array = convert_part_to_arg(data, cmd, 0);
		exec_cmd_no_pipe(data, cmd_array);
	}
	else
	{
		pipe(pipes);
		while (cmd_index <= data->nb_pipes)
		{
			cmd_array = convert_part_to_arg(data, cmd+cmd_index, 0);
			exec_cmd_with_pipe(data, cmd_array, pipes);
			cmd_index++;
		}
		rl_replace_line(" ", 0);
	}
}
