/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:28:11 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/03 18:09:44 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

static void	pars_redir_if_0(char *input, char *new_input, int i[3])
{
	if (input[i[0]] == '\'' || input[i[0]] == '\"')
	{
		i[2] = skip_quote(input, i[0]);
		while (i[0] != i[2])
		{
			new_input[i[1]] = input[i[0]];
			i[0]++;
			i[1]++;
		}
	}
}

static int	pars_redir_if_1(char *input, t_cmd *cmd, t_data *data, int i[3])
{
	if (input[i[0] + 1] == '>')
	{
		i[2] = handle_outfile(input + i[0] + 1, cmd, data);
		if (!i[2])
			return (1);
		i[0] += i[2];
	}
	else
	{
		i[2] = handle_infile(input + i[0], cmd, data);
		if (!i[2])
			return (1);
		i[0] += i[2];
	}
	return (0);
}

static int	pars_redir_if_2(char *input, char *new_input, t_cmd *cmd, int i[3], t_data *data)
{
	if (input[i[0]] == '>')
	{
		i[2] = handle_outfile(input + i[0], cmd, data);
		if (!i[2])
			return (1);
		i[0] += i[2];
	}
	else
	{
		new_input[i[1]] = input[i[0]];
		i[1]++;
		i[0]++;
	}
	return (0);
}

//i[0] = i
//i[1] = j
//i[2] = tmp
char	*pars_redir(char *input, t_cmd *cmd, t_data *data)
{
	int		i[3];
	char	*new_input;

	i[0] = 0;
	if (!is_redir(input))
		return (input);
	new_input = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	i[1] = 0;
	while (input[i[0]])
	{
		pars_redir_if_0(input, new_input, i);
		if (input[i[0]] == '<')
			if (pars_redir_if_1(input, cmd, data, i))
				return (NULL);
		if (pars_redir_if_2(input, new_input, cmd, i, data))
			return (NULL);
	}
	//free(input);
	return (new_input);
}
