/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:26:39 by authomas          #+#    #+#             */
/*   Updated: 2025/09/02 19:30:22 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int is_redir(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
        if (input[i] == '\'' || input[i] == '\"')
			i += skip_quote(input, i);
		if (input[i] == '<')
            return (1);
		if (input[i] == '>')
			return (1);
		i++;
	}
    return(0);
}

int handle_heredoc(char *input, t_cmd *cmd, t_data *data)
{
    int i;
    int j;
    char *name;

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
        name = expand(input + j, i - j, data);
    else
        name = ft_strndup(input + j, i - j);
    if(!name)
        return (0);
    if (cmd->infile != -1)
        close(cmd->infile);
    cmd->infile = here_doc(name, data);
    cmd->here_doc = 1;
    cmd->hd_name = name;
    return (i);
}

int handle_infile(char *input, t_cmd *cmd, t_data *data)
{
    int i;
    int j;
    char *name;

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
            name = expand(input + j, i - j, data);
        else
            name = ft_strndup(input + j, i - j);
        if(!name)
            return (0);
        if (cmd->infile != -1)
            close(cmd->infile);
        cmd->infile = open(name, O_RDONLY);
        free(name);
    }
    return (i);
}

int handle_outfile(char *input, t_cmd *cmd, t_data *data)
{
    int i;
    int j;
    char *name = NULL;

    i = 1;
    if (!input[i] || input[i] == '<')
        return (0);
    if (input[i] == '>')
    {
        i++;
        while (input[i] && ft_isspace(input[i]))
            i++;
        j = i;
        if (!input[i] || input[i] == '<')
            return (0);
        while (input[i] && !ft_isspace(input[i]))
            i++;
        if (input[j] == '$')
            name = expand(input + j, i - j, data);
        else
            name = ft_strndup(input + j, i - j);
        if(!name)
            return (0);
        if (cmd->outfile != -1)
            close(cmd->outfile);
        cmd->outfile = open(name, O_CREAT | O_APPEND | O_WRONLY, 0644);
    }
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
            name = expand(input + j, i - j, data);
        else
            name = ft_strndup(input + j, i - j);
        if(!name)
            return (0);
        if (cmd->outfile != -1)
            close(cmd->outfile);
        cmd->outfile = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    }
    free(name);
    return (i);
}

char *pars_redir(char *input, t_cmd *cmd, t_data *data)
{
	int i;
    int j;
    int tmp;
    char *new_input;

	i = 0;
    cmd->infile = -1;
    cmd->outfile = -1;
    cmd->here_doc = -1;
    if (!is_redir(input))
        return (input);
    new_input = ft_calloc(sizeof(char), ft_strlen(input) + 1);
    j = 0;
	while(input[i])
	{
        if (input[i] == '\'' || input[i] == '\"')
		{
			tmp = skip_quote(input, i);
            while (i != tmp)
            {
                new_input[j] = input[i];
                i++;
                j++;
            }
		}
		else if (input[i] == '<')
		{
            if (input[i + 1] == '>')
            {
                tmp = handle_outfile(input + i + 1, cmd, data);
                if (!tmp)
                    return (NULL);
                i += tmp;
            }
            else
            {
                tmp = handle_infile(input + i, cmd, data);
                if (!tmp)
                    return (NULL);
			    i += tmp;
            }
		}
		else if (input[i] == '>')
		{
            tmp = handle_outfile(input + i, cmd, data);
                if (!tmp)
                    return (NULL);
                i += tmp;
		}
        else
        {
            new_input[j] = input[i];
            j++;
            i++;
        }
	}
    return (new_input);
}
