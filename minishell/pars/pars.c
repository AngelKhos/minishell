/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/07/02 17:05:15 by authomas         ###   ########lyon.fr   */
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

// void	alloc_cmd(t_data *data, char **cmd_str)
// {
// 	size_t	i;
// 	size_t	size;
// 	int		cmd_index;
// 	int		is_cmd;
// 	int		part_i;
	
// 	// is_cmd = 0;
// 	// part_i = 0;
// 	cmd_index = 0;
// 	// size = 0;
// 	i = 0;
// 	// while (cmd_str[size] && ft_strncmp(cmd_str[i + size], "|", -1) != 0)
// 	// 	size++;
// 	// data->cmd[0].parts = ft_calloc(sizeof(t_part), size);
// 	// data->cmd[0].len = size;
// 	while (cmd_str[i])
// 	{
// 		if (ft_strncmp(cmd_str[i], "|", -1) == 0)
// 		{
// 			is_cmd = 0;
// 			i++;
// 			cmd_index++;
// 			size = 0;
// 			part_i = 0;
// 			while (cmd_str[i + size] && ft_strncmp(cmd_str[i + size], "|", -1) != 0)
// 				size++;
// 			data->cmd[cmd_index].len = size;
// 			data->cmd[cmd_index].parts = ft_calloc(sizeof(t_part), size);
// 		}
// 		data->cmd[cmd_index].parts[part_i].str = ft_strdup(cmd_str[i]);
// 		if (is_cmd == 0)
// 		{
// 			is_cmd = 1;
// 			data->cmd[cmd_index].parts[part_i].type = CMD;
// 		}
// 		else
// 			data->cmd[cmd_index].parts[part_i].type = ARG;
// 		i++;
// 		part_i++;
// 		//:)
// 	}
// }

void alloc_cmd(t_data *data, char **inputs)
{
	char **raw_cmd;
	size_t i;
	size_t part_i;

	i = 0;
	while (inputs[i])
	{
		part_i = 0;
		raw_cmd = ms_split(inputs[i], ' ');
		data->cmd[i].len = get_tablen(raw_cmd);
		data->cmd[i].parts = ft_calloc(sizeof(t_part), get_tablen(raw_cmd));
		data->cmd[i].infile = -1;
		data->cmd[i].outfile = -1;
		while(raw_cmd[part_i])
		{
			data->cmd[i].parts[part_i].str = ft_strdup(raw_cmd[part_i]);
			if (i == 0)
			{
				data->cmd[i].parts[part_i].type = CMD;
			}
			else
			{
				data->cmd[i].parts[part_i].type = ARG;
			}
			part_i++;
		}
		free_array(raw_cmd);
		i++;
	}

}

// if ("<<")
// 	data->cmd[i].infile = heredoc(data, delimiter);
// if (">")
// 	change le outfile a un open du fichier qui est donné apres
// if ("<")
// 	change le infile a un open du fichier qui est donné avant

// void print_split(char **inputs)
// {
// 	int i = 0;

// 	while (inputs[i])
// 	{
// 		ft_printf("%d : %s\n", i, inputs[i]);
// 		i++;
// 	}
// }

int parsing(t_data *data)
{
	char	**inputs;
	
	inputs = ms_split(data->input, '|');
	print_split(inputs);
	if (!inputs)
	{
		ft_printf("parsing error");
		return (0);
	}
	data->nb_pipes = get_tablen(inputs) - 1;
	data->cmd = malloc(sizeof(t_cmd) * (data->nb_pipes + 1));
	if (!data->cmd)
		return (0);
	alloc_cmd(data, inputs);
	return (1);
}

// split les pipes pour avoir les commandes puis split les args
// quotes faire gaffe a pas faire des bails chelou genre un pipe dans un quote
// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou