/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:20:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/02 16:48:02 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

char	*convert_part_to_arg(t_data *data, t_cmd *cmd, int index)
{
	int		size;
	int		i;
	char	*cmd_plus_arg;

	(void)data;
	cmd_plus_arg = NULL;
	i = 0;
	size = 1;
	while (cmd->parts[index+size].type == ARG)
		size++;
	while (i < size)
	{
		//ft_printf("str %s\n", cmd->parts[i].str);
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, " ");
		cmd_plus_arg = ft_strjoin(cmd_plus_arg, cmd->parts[i].str);
		i++;
	}
	//ft_printf("cpta : %s\n", cmd_plus_arg);
	return (cmd_plus_arg);
}

void	exec_cmd_no_pipe(t_data *data, t_cmd *cmd, int index)
{
	int		pid;
	char	*cmd_array;

	cmd_array = convert_part_to_arg(data, cmd, index);
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

void	read_cmd(t_data *data, t_cmd *cmd)
{
	int	i;
	int	have_pipe;
	int	nb_arg;

	i = -1;
	have_pipe = 0;
	nb_arg = 0;
	while (++i <= cmd->len)
	{
		if (cmd->parts[i].type == CMD)
		{
			exec_cmd_no_pipe(data, cmd, i);
		}
	}
}
