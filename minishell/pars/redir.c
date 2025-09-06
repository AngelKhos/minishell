/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:26:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/06 16:50:46 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	is_redir(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quote(input, i);
		if (input[i] && input[i] == '<')
			return (1);
		if (input[i] && input[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	handle_heredoc(char *input, t_cmd *cmd, t_data *data)
{
	size_t	i;
	size_t	j;
	char	*name;

	i = 1;
	if (!input[i])
		return (0);
	while (input[i] && ft_isspace(input[i]))
		i++;
	j = i;
	if (!input[i] || input[i] == '<' || input[i] == '>')
		return (0);
	while (input[i] && !ft_isspace(input[i]))
		i++;
	if (input[j] == '$')
		name = get_expand(input + j, i - j, data);
	else
		name = ft_strndup(input + j, i - j);
	if (!name)
		return (0);
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = here_doc(name, data);
	if (cmd->infile == -1)
		return (unlink(name), free(name), i);
	cmd->here_doc = 1;
	cmd->hd_name = name;
	return (i);
}

int	handle_infile(char *input, t_cmd *cmd, t_data *data)
{
	size_t	i;
	size_t	j;
	char	*name;

	i = 1;
	if (!input[i])
		return (0);
	if (input[i++] == '<')
		i += handle_heredoc(input + i, cmd, data);
	else
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		j = i;
		if (!input[i] || input[i] == '<' || input[i] == '>')
			return (0);
		while (input[i] && !ft_isspace(input[i]))
			i++;
		if (input[j] == '$')
			name = get_expand(input + j, i - j, data);
		else
			name = ft_strndup(input + j, i - j);
		if (!name)
			return (0);
		if (cmd->infile != -1)
			close(cmd->infile);
		cmd->infile = open(name, O_RDONLY);
		free(name);
	}
	return (i);
}
