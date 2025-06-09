/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/09 17:23:46 by gchauvet         ###   ########.fr       */
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
	while (cmd[0].parts[index+size].type == ARG)
		size++;
	while (i < size)
	{
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, " ");
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, cmd[0].parts[i].str);
		i++;
	}
	return (cmd_plus_arg);
}

void	exec_cmd(t_data *data, char *cmd_str, int **pipes, int *pids, int cmd_index)
{
	pipe(pipes[cmd_index]);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		if (data->nb_pipes > 0)
		{
			if (cmd_index > 0)
				dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
			if (cmd_index < data->nb_pipes)
				dup2(pipes[cmd_index][1], STDOUT_FILENO);
			close(pipes[cmd_index][0]);
			close(pipes[cmd_index][1]);
		}
		ft_printf("cpta : %s\n", cmd_str);
		execute(cmd_str, data->envp);
		exit(0);
	}
}

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int		cmd_index;
	char	*cmd_str;
	int		**pipes;
	int		*pids;

	pipes = malloc(sizeof(int *) * data->nb_pipes + 1);
	pids = malloc(sizeof(int) * data->nb_pipes + 1);
	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		if (data->nb_pipes > 0 && cmd_index < data->nb_pipes)
			pipes[cmd_index] = malloc(sizeof(int) * 2);
		ft_printf("execution du pip : %i\n", cmd_index);
		ft_printf("nb_pipes %i\n", data->nb_pipes);
		cmd_str = convert_part_to_arg(data, cmd+cmd_index, 0);
		exec_cmd(data, cmd_str, pipes, pids, cmd_index);
		cmd_index++;
	}
	if (data->nb_pipes > 0)
	{
		cmd_index = 0;
		while (cmd_index <= data->nb_pipes)
		{
			close(pipes[cmd_index][0]);
			close(pipes[cmd_index][1]);
			free(pipes[cmd_index]);
			cmd_index++;
		}
	}
	free(pipes);
	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		ft_printf("je suis la\n");
		waitpid(pids[cmd_index], NULL, 0);
		cmd_index++;
	}
	free(pids);
}
