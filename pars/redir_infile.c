/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:26:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/10 19:42:17 by authomas         ###   ########lyon.fr   */
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

char	*get_name(char *input, int i, int j, t_data *data)
{
	char	*name;

	if (input[j] == '$')
		name = get_expand(input + j, i - j, data);
	else
		name = ft_strndup(input + j, i - j);
	return (name);
}

int	handle_heredoc(char *input, t_cmd *cmd, t_data *data)
{
	size_t	i;
	size_t	j;
	char	*name;

	i = 0;
	if (!input[i])
		return (unexpected_token(data, 1));
	while (input[i] && ft_isspace(input[i]))
		i++;
	j = i;
	if (!input[i] || is_in_out(input[i]))
		return (unexpected_token(data, 1));
	while (input[i] && !ft_isspace(input[i]) && !is_in_out(input[i]))
		i++;
	name = get_name(input, i, j, data);
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

int	handle_infile_loop(char *input, t_cmd *cmd, t_data *data)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	if (!input)
		return (unexpected_token(data, 1));
	while (input[i] && ft_isspace(input[i]))
		i++;
	j = i;
	if (!input[i] || input[i] == '<' || input[i] == '>')
		return (unexpected_token(data, 1));
	while (input[i] && !ft_isspace(input[i]) && !is_in_out(input[i]))
		i++;
	name = get_name(input, i, j, data);
	if (!name)
		return (0);
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(name, O_RDONLY);
	if (permission_denied(1, name, data))
		return (0);
	free(name);
	return (i);
}

int	handle_infile(char *input, t_cmd *cmd, t_data *data)
{
	size_t	i;
	size_t	tmp;

	i = 1;
	if (!input[i])
		return (unexpected_token(data, 1));
	if (input[i++] == '<')
	{
		if (cmd->hd_name)
			close_here_doc(cmd);
		tmp = handle_heredoc(input + i, cmd, data);
		if (!tmp)
			return (0);
		i += tmp;
	}
	else
	{
		i--;
		tmp = handle_infile_loop(input + i, cmd, data);
		if (!tmp)
			return (0);
		i += tmp;
	}
	return (i);
}
