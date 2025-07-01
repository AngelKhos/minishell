/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/07/01 17:39:11 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	get_tablen(char **inputs)
{
	size_t	i;

	i = 0;
	while (inputs[i])
	{
		i++;
	}
	return (i);
}

void	alloc_cmd(t_data *data, char **cmd_str)
{
	size_t	i;
	size_t	size;
	int		cmd_index;
	int		is_cmd;
	int		part_i;
	
	is_cmd = 0;
	part_i = 0;
	cmd_index = 0;
	size = 0;
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
			part_i = 0;
			while (cmd_str[i + size] && ft_strncmp(cmd_str[i + size], "|", -1) != 0)
				size++;
			data->cmd[cmd_index].len = size;
			data->cmd[cmd_index].parts = ft_calloc(sizeof(t_part), size);
		}
		data->cmd[cmd_index].parts[part_i].str = ft_strdup(cmd_str[i]);
		if (is_cmd == 0)
		{
			is_cmd = 1;
			data->cmd[cmd_index].parts[part_i].type = CMD;
		}
		else
			data->cmd[cmd_index].parts[part_i].type = ARG;
		i++;
		part_i++;
		//:)
	}
}

void print_split(char **inputs)
{
	int i = 0;

	while (inputs[i])
	{
		ft_printf("%d : %s\n", i, inputs[i]);
		i++;
	}
}

int parsing(t_data *data)
{
	char	**inputs;
	
	inputs = ms_split(data->input, '|');
	if (!inputs)
	{
		ft_printf("parsing error");
		return (0);
	}
	print_split(inputs);
	data->nb_pipes = get_tablen(inputs) - 1;
	data->cmd = malloc(sizeof(t_cmd) * (data->nb_pipes + 1));
	alloc_cmd(data, inputs);
	return (1);
}

// split les pipes pour avoir les commandes puis split les args
// quotes faire gaffe a pas faire des bails chelou genre un pipe dans un quote
// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou