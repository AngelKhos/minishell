/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:15:41 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/03 17:13:32 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/data.h"
#include <linux/limits.h>
#include <readline/chardefs.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

int	get_nb_pipes(t_data *data, char **cmd_str)
{
	int	nb_pipes;
	size_t	i;

	nb_pipes = 0;
	i = 0;
	while (cmd_str[i])
	{
		if (ft_strncmp(cmd_str[i], "|", -1) == 0)
			nb_pipes++;
		i++;
	}
	return nb_pipes;
}

void	alloc_cmd_no_pipes(t_data *data, char **cmd_str)
{
	size_t	i;
	size_t	size;
	int		is_cmd;
	
	is_cmd = 0;
	i = 0;
	while (cmd_str[size])
		size++;
	data->cmd->parts = ft_calloc(sizeof(t_part), size);
	data->cmd[0].len = size;
	while (cmd_str[i])
	{
		data->cmd[0].parts[i].str = ft_strdup(cmd_str[i]);
		if (is_cmd == 0)
		{
			is_cmd = 1;
			data->cmd[0].parts[i].type = CMD;
		}
		else
			data->cmd[0].parts[i].type = ARG;
		i++;
	}
}

void	alloc_cmd_with_pipes(t_data *data, char **cmd_str)
{
	size_t	i;
	size_t	size;
	int		cmd_index;
	int		is_cmd;
	
	is_cmd = 0;
	cmd_index = 0;
	i = 0;
	while (cmd_str[size] && ft_strncmp(cmd_str[i + size], "|", -1) != 0)
		size++;
	data->cmd[0].parts = ft_calloc(sizeof(t_part), size);
	data->cmd[0].len = size;
	while (cmd_str[i])
	{
		if (ft_strncmp(cmd_str[i], "|", -1) == 0)
		{
			is_cmd = 0;
			i++;
			cmd_index++;
			size = 0;
			while (cmd_str[i + size] && ft_strncmp(cmd_str[i + size], "|", -1) != 0)
				size++;
			data->cmd[cmd_index].parts = ft_calloc(sizeof(t_part), size);
		}
		data->cmd[cmd_index].parts[i].str = ft_strdup(cmd_str[i]);
		if (is_cmd == 0)
		{
			is_cmd = 1;
			data->cmd[cmd_index].parts[i].type = CMD;
		}
		else
			data->cmd[cmd_index].parts[i].type = ARG;
		i++;
	}
}

void	fake_parsing(t_data *data)
{
	char	**cmd_str;
	int		cmd_index;
	
	cmd_str = ft_split(data->input, ' ');
	data->nb_pipes = get_nb_pipes(data, cmd_str);
	data->cmd = malloc(sizeof(t_cmd) * data->nb_pipes + 2);
	if (data->nb_pipes >= 1)
	{

	}
	else
	{
		alloc_cmd_no_pipes(data, cmd_str);
	}
}