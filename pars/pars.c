/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/09/10 18:57:59 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	rm_quotes(char **split)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		cpy = strdup_wquotes(split[i]);
		split[i] = cpy;
		i++;
	}
}

void	alloc_when(t_data *data, int i, int part_i)
{
	free(data->cmd[i].parts);
	data->cmd[i].parts = ft_calloc(sizeof(t_part), 1);
	if (!data->cmd[i].parts)
		return ;
	data->cmd[i].parts[part_i].str = NULL;
	data->cmd[i].parts[part_i].type = CMD;
}

void	alloc_cmd_part_2(char **raw_cmd, t_data *data, size_t i, int is_cmd)
{
	size_t	part_i;

	part_i = 0;
	rm_quotes(raw_cmd);
	data->cmd[i].len = get_tablen(raw_cmd);
	data->cmd[i].parts = ft_calloc(sizeof(t_part), get_tablen(raw_cmd));
	if (!raw_cmd)
		return (alloc_when(data, i, part_i));
	if (!data->cmd[i].parts)
		return (free_array(raw_cmd));
	while (raw_cmd[part_i])
	{
		data->cmd[i].parts[part_i].str = ft_strdup(raw_cmd[part_i]);
		if (is_cmd == 0)
		{
			if (is_builtins(raw_cmd[part_i]))
				data->cmd[i].parts[part_i].type = BUIL;
			else
				data->cmd[i].parts[part_i].type = CMD;
		}
		else
			data->cmd[i].parts[part_i].type = ARG;
		part_i++;
	}
	free_array(raw_cmd);
}

int	alloc_cmd(t_data *data, char **inputs)
{
	char	**raw_cmd;
	char	*parsed_input;
	size_t	i;
	int		is_cmd;

	i = 0;
	while (inputs[i])
	{
		data->cmd[i].infile = -1;
		data->cmd[i].outfile = -1;
		data->cmd[i].here_doc = -1;
		is_cmd = 0;
		parsed_input = pars_redir(inputs[i], &data->cmd[i], data);
		if (!parsed_input)
			return (0);
		raw_cmd = ms_split(parsed_input, ' ');
		free(parsed_input);
		if (i == 0 && !raw_cmd)
			return (0);
		if (!pars_exp(data, raw_cmd))
			return (free_array(raw_cmd), 0);
		alloc_cmd_part_2(raw_cmd, data, i, is_cmd);
		i++;
	}
	return (1);
}

int	parsing(t_data *data)
{
	char	**inputs;

	if (!checking_missing_command(data->input))
		return (unexpected_token(data, 2));
	inputs = ms_split(data->input, '|');
	if (!inputs)
	{
		ft_dprintf(2, "Error: error in parsing\n");
		return (0);
	}
	data->nb_pipes = get_tablen(inputs) - 1;
	data->cmd = ft_calloc(sizeof(t_cmd), (data->nb_pipes + 1));
	if (!data->cmd || data->nb_pipes > PIPE_LIMIT)
	{
		ft_dprintf(2, "Error: error in parsing\n");
		if (data->cmd)
			free(data->cmd);
		return (free_array(inputs), 0);
	}
	if (!alloc_cmd(data, inputs))
		return (close_file(data), free(inputs), free(data->cmd), 0);
	return (free(inputs), 1);
}

// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou