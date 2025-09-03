/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:04:37 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/03 14:22:15 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

static int	handle_outfile_if_1(char *input, t_cmd *cmd, int i[2], char *name, t_data *data)
{
	i[0]++;
	while (input[i[0]] && ft_isspace(input[i[0]]))
		i[0]++;
	i[1] = i[0];
	if (!input[i[0]] || input[i[0]] == '<')
		return (0);
	while (input[i[0]] && !ft_isspace(input[i[0]]))
		i[0]++;
	if (input[i[1]] == '$')
        name = expand(input + i[1], i[0] - i[1], data);
	else
		name = ft_strndup(input + i[1], i[0] - i[1]);
	if(!name)
		return (0);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(name);
	return (1);
}

static int	handle_outfile_if_2(char *input, t_cmd *cmd, int i[2], char *name, t_data *data)
{
	while (input[i[0]] && ft_isspace(input[i[0]]))
		i[0]++;
	i[1] = i[0];
	if (!input[i[0]] || input[i[0]] == '<' || input[i[0]] == '>')
		return (0);
	while (input[i[0]] && !ft_isspace(input[i[0]]))
		i[0]++;
	if (input[i[1]] == '$')
		name = expand(input + i[1], i[0] - i[1], data);
	else
		name = ft_strndup(input + i[1], i[0] - i[1]);
	if(!name)
		return (0);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(name);
	return (1);
}

int	handle_outfile(char *input, t_cmd *cmd, t_data *data)
{
	int		i[2];
	char	*name;

	i[0] = 1;
	i[1] = 0;
	name = NULL;
	if (!input[i[0]] || input[i[0]] == '<')
		return (0);
	if (input[i[0]] == '>')
	{
		if (handle_outfile_if_1(input, cmd, i, name, data) == 0)
			return (0);
	}
	else
	{
		if (handle_outfile_if_2(input, cmd, i, name, data) == 0)
			return (0);
	}
	return (i[0]);
}
