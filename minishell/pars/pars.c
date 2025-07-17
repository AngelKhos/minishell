/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:11:18 by authomas          #+#    #+#             */
/*   Updated: 2025/07/17 15:53:53 by authomas         ###   ########lyon.fr   */
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

void pars_redir(char *input, t_cmd *cmd)
{
	//int i;
	//int j;
	char *file;

	//i = 0;
	file = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	(void)input;
	// while(input[i])
	// {
	// 	if (input[i] == '<')
	// 	{
	// 		i++;
	// 		while(input[i] == ' ')
	// 			i++;
	// 		j = i;
	// 		while(ft_isalnum(input[j]))
	// 			j++;
	// 		file = ft_substr(input, i, j - i);
	// 		cmd->infile = open(file, O_RDONLY);
	// 		if (cmd->infile == -1)
	// 			ft_printf("pa conten");
	// 	}
	// 	else if (input[i] == '>')
	// 	{
	// 		i++;
	// 		while(input[i] == ' ')
	// 			i++;
	// 		j = i;
	// 		while(ft_isalnum(input[j]))
	// 			j++;
	// 		file = ft_substr(input, i, j - i);
	// 		cmd->outfile = open(file, O_CREAT | O_WRONLY);
	// 		if (cmd->outfile == -1)
	// 			ft_printf("pa conten");
	// 	}
	// 	i++;
	// }//:)
	if (file)
		free(file);
}

int alloc_cmd(t_data *data, char **inputs)
{
	char **raw_cmd;
	size_t i;
	size_t part_i;
	int is_cmd;

	i = 0;
	while (inputs[i])
	{
		part_i = 0;
		is_cmd = 0;
		pars_redir(inputs[i], &data->cmd[i]);
		raw_cmd = ms_split(inputs[i], ' ');
		if (!raw_cmd)
			return (0);
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
	}
	return (1);
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
	return (1);
}

int parsing(t_data *data)
{
	char	**inputs;
	
	if (!checking_missing_command(data->input))
	{
		ft_printf("Error: invalid arguments near token '|'\n");
		return (0);
	}
	inputs = ms_split(data->input, '|');
	if (!inputs)
	{
		ft_printf("Error: malloc error in parsing function\n");
		return (0);
	}
	data->nb_pipes = get_tablen(inputs) - 1;
	data->cmd = ft_calloc(sizeof(t_cmd), (data->nb_pipes + 1));
	if (!data->cmd)
	{
		ft_printf("Error: malloc error in parsing function\n");
		return (0);
	}
	if(!alloc_cmd(data, inputs))
		return (0);
	return (1);
}

// quotes faire gaffe a pas faire des bails chelou genre un pipe dans un quote
// simple quote traduit pas, double quote traduit les $var
// les $ peuvent etre n'importe ou