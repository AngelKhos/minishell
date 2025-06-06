/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/06 16:08:09 by gchauvet         ###   ########.fr       */
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

void	exec_cmd_no_pipe(t_data *data, char *cmd_str)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		execute(cmd_str, data->envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	exec_cmd_with_pipe(t_data *data, char *cmd_str, int pipes[2], int cmd_index)
{
	int		pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (cmd_index > 0)
			dup2(pipes[0], STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		execute(cmd_str, data->envp);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int		nb_arg;
	int		cmd_index;
	char	*cmd_str;
	int		pipes[2];

	cmd_index = 0;
	nb_arg = 0;
	while (cmd_index <= data->nb_pipes)
	{
		pipe(pipes);
		//ft_printf("execution du pip : %i\n", cmd_index);
		cmd_str = convert_part_to_arg(data, cmd+cmd_index, 0);
		if (cmd_index < data->nb_pipes)
		{
			exec_cmd_with_pipe(data, cmd_str, pipes, cmd_index);
		}
		else if (cmd_index >= data->nb_pipes)
		{
			exec_cmd_no_pipe(data, cmd_str);
		}
		cmd_index++;
	}
}
