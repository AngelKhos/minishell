/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:04:37 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/28 19:44:07 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

static int	handle_outfile_append(char *input,
				t_cmd *cmd, int i[2], t_data *data)
{
	char	*name;

	name = NULL;
	i[0]++;
	while (input[i[0]] && ft_isspace(input[i[0]]))
		i[0]++;
	i[1] = i[0];
	if (!input[i[0]] || is_in_out(input[i[0]]))
		return (unexpected_token(1, data));
	while (input[i[0]] && !ft_isspace(input[i[0]]) && !is_in_out(input[i[0]]))
	{
		if (input[i[0]] == '\"' || input[i[0]] == '\'')
			i[0] = skip_quote(input, i[0]);
		i[0]++;
	}
	name = get_name(input, i[0], i[1], data, 0);
	if (!name)
		return (0);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (permission_denied(2, name, data))
		return (0);
	free(name);
	return (1);
}

static int	handle_outfile_trunc(char *input, t_cmd *cmd,
				int i[2], t_data *data)
{
	char	*name;

	name = NULL;
	while (input[i[0]] && ft_isspace(input[i[0]]))
		i[0]++;
	i[1] = i[0];
	if (!input[i[0]] || is_in_out(input[i[0]]))
		return (unexpected_token(1, data));
	while (input[i[0]] && !ft_isspace(input[i[0]]) && !is_in_out(input[i[0]]))
	{
		if (input[i[0]] == '\"' || input[i[0]] == '\'')
			i[0] = skip_quote(input, i[0]);
		i[0]++;
	}
	name = get_name(input, i[0], i[1], data, 0);
	if (!name)
		return (0);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (permission_denied(2, name, data))
		return (0);
	free(name);
	return (1);
}

int	handle_outfile(char *input, t_cmd *cmd, t_data *data)
{
	int	i[2];

	i[0] = 1;
	i[1] = 0;
	if (!input[i[0]] || input[i[0]] == '<')
		return (unexpected_token(1, data));
	if (input[i[0]] == '>')
	{
		if (handle_outfile_append(input, cmd, i, data) == 0)
			return (0);
	}
	else
	{
		if (handle_outfile_trunc(input, cmd, i, data) == 0)
			return (0);
	}
	return (i[0]);
}
