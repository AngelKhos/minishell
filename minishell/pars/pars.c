/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/06/16 16:02:53 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	get_nb_pipes(char **inputs)
{
	int	nb_pipes;
	size_t	i;

	nb_pipes = 0;
	i = 0;
	while (inputs[i])
	{
		if (ft_strncmp(inputs[i], "|", -1) == 0)
			nb_pipes++;
		i++;
	}
	return nb_pipes;
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

// int checking_missing_stuff(char *inputs)
// {
// 	int i = 0;

// 	while(inputs[i])
// 	{
		
// 		if (ft_strncmp(inputs[i], "|", -1) == 0 && !inputs[i + 1])
// 			return (1);
// 		// mettre un parsing error si il manque un quote
// 	}
// 	return (0); // <------------------- j'ai ajouter ça pour pouvoir compiler
// }

void parsing(t_data *data)
{
	char	**inputs;
	
	inputs = ft_split(data->input, ' ');
	if (!inputs)
		return;
	data->nb_pipes = get_nb_pipes(inputs);
	data->cmd = malloc(sizeof(t_cmd) * (data->nb_pipes + 1));
	alloc_cmd(data, inputs);
}

// split les pipes pour avoir les commandes puis split les args
// quotes faire gaffe a pas faire des bails chelou genre un pipe dans un quote
// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou