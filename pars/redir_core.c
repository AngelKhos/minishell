/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:28:11 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/14 15:03:32 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

static void	pars_redir_quote(char *input, t_redir *redir)
{
	if (input[redir->i] == '\'' || input[redir->i] == '\"')
	{
		redir->tmp = skip_quote(input, redir->i);
		while (redir->i != redir->tmp)
		{
			redir->new_input[redir->j] = input[redir->i];
			redir->i++;
			redir->j++;
		}
	}
}

static int	pars_redir_infile(char *input, t_cmd *cmd,
	t_data *data, t_redir *redir)
{
	if (input[redir->i + 1] == '>')
	{
		redir->tmp = handle_outfile(input + redir->i + 1, cmd, data);
		if (!redir->tmp)
			return (1);
		redir->i += redir->tmp;
	}
	else
	{
		redir->tmp = handle_infile(input + redir->i, cmd, data);
		if (!redir->tmp)
			return (1);
		redir->i += redir->tmp;
	}
	return (0);
}

static int	pars_redir_outfile(char *input, t_redir *redir,
	t_cmd *cmd, t_data *data)
{
	if (input[redir->i] == '>')
	{
		redir->tmp = handle_outfile(input + redir->i, cmd, data);
		if (!redir->tmp)
			return (1);
		redir->i += redir->tmp;
	}
	else
	{
		redir->new_input[redir->j] = input[redir->i];
		redir->i++;
		redir->j++;
	}
	return (0);
}

char	*pars_redir(char *input, t_cmd *cmd, t_data *data)
{
	t_redir	*redir;
	char	*new_input;

	if (!is_redir(input))
		return (ft_strdup(input));
	redir = ft_calloc(sizeof(t_redir), 1);
	redir->i = 0;
	redir->new_input = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (!redir->new_input)
		return (free(redir), NULL);
	redir->j = 0;
	while (redir->i < ft_strlen(input))
	{
		pars_redir_quote(input, redir);
		if (input[redir->i] == '<')
			if (pars_redir_infile(input, cmd, data, redir))
				return (free(redir->new_input), free(redir), NULL);
		if (pars_redir_outfile(input, redir, cmd, data))
			return (free(redir->new_input), free(redir), NULL);
	}
	new_input = redir->new_input;
	free(redir);
	return (new_input);
}
