/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/08/24 17:06:58 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	get_tablen(char **inputs)
{
	size_t	i;

	i = 0;
	if (inputs)
		while (inputs[i])
			i++;
	return (i);
}

void rm_quotes(char **split)
{
	int i;
	char *cpy;

	i = 0;

	while (split[i])
	{
		cpy = strdup_wquotes(split[i]);
		split[i] = cpy;
		i++;
	}
}

int alloc_cmd(t_data *data, char **inputs)
{
	char **raw_cmd;
	char *parsed_input;
	size_t i;
	size_t part_i;
	int is_cmd;

	i = 0;
	while (inputs[i])
	{
		part_i = 0;
		is_cmd = 0;
		parsed_input = pars_redir(inputs[i], &data->cmd[i]);
		if(!parsed_input)
		{
			ft_dprintf(2, "Error: unexpected token\n");
			return (0);
		}
		raw_cmd = ms_split(parsed_input, ' ');
		//expand(data, raw_cmd);
		if (!raw_cmd)
			return (0);
		rm_quotes(raw_cmd);
		data->cmd[i].len = get_tablen(raw_cmd);
		data->cmd[i].parts = ft_calloc(sizeof(t_part), get_tablen(raw_cmd));
		while(raw_cmd[part_i])
		{
			data->cmd[i].parts[part_i].str = ft_strdup(raw_cmd[part_i]);
			if (is_cmd == 0)
			{
				if (ft_strnstr("echo, cd, env, exit, pwd, export, unset", raw_cmd[part_i], -1))
					data->cmd[i].parts[part_i].type = BUIL;
				else
					data->cmd[i].parts[part_i].type = CMD;
			}
			else
				data->cmd[i].parts[part_i].type = ARG;
			part_i++;
		}
		free_array(raw_cmd);
		i++;
	}//:)
	return (1);
}

int checking_missing_command(char *input)
{
	int i;
	char *str;

	str = ft_strtrim(input, " \r\t\v\f");
	if (!str || str[0] == '|')
	{
		free(str);
		return (0);
	}
	i = 0;
	while(str[i])
	{	
		if (str[i] == '|')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' 
				|| str[i] == '\r' || str[i] == '\f'))
				i++;
			if (!str[i] || str[i] == '|')
				return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

int parsing(t_data *data)
{
	char	**inputs;
	
	if (!checking_missing_command(data->input))
	{
		ft_dprintf(2, "Error: invalid arguments near token '|'\n");
		return (0);
	}
	inputs = ms_split(data->input, '|');
	if (!inputs)
	{
		ft_dprintf(2, "Error: error in parsing function\n");
		return (0);
	}
	data->nb_pipes = get_tablen(inputs) - 1;
	data->cmd = ft_calloc(sizeof(t_cmd), (data->nb_pipes + 1));
	if (!data->cmd)
	{
		ft_dprintf(2, "Error: error in parsing function\n");
		return (0);
	}
	if(!alloc_cmd(data, inputs))
	{
		ft_dprintf(2, "Error: unable to allocate command in parsing function\n");
		return (0);
	}
	free(inputs);
	return (1);
}

// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou