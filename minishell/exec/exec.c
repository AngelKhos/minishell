/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/10 17:12:13 by gchauvet         ###   ########.fr       */
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

void	exec_cmd(t_data *data, char *cmd_str, int pipes[2], int *pids, int cmd_index)
{
	pipe(pipes);
	pids[cmd_index] = fork();
	if (pids[cmd_index] == 0)
	{
		if (data->nb_pipes > 0)
		{
			if (cmd_index > 0)
			{
				dup2(pipes[0], STDIN_FILENO);
				ft_printf("copy de read pipe vers STDIN de %s\n", cmd_str);
			}
			if (cmd_index < data->nb_pipes)
			{
				dup2(pipes[1], STDOUT_FILENO);
				ft_printf("copy de STDOUT vers write pipe de %s\n", cmd_str);
			}
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
	int		pipes[2];
	int		*pids;

	cmd_index = 0;
	pids = malloc(sizeof(int) * data->nb_pipes + 1);
	while (cmd_index <= data->nb_pipes)
	{
		ft_printf("execution du pip : %i\n", cmd_index);
		cmd_str = convert_part_to_arg(data, cmd+cmd_index, 0);
		exec_cmd(data, cmd_str, pipes, pids, cmd_index);
		cmd_index++;
	}
	cmd_index = 0;
	while (cmd_index <= data->nb_pipes)
	{
		waitpid(pids[cmd_index], NULL, 0);
		cmd_index++;
	}
	close(pipes[0]);
	close(pipes[1]);
	free(pids);
}
