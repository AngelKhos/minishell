/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:26:39 by authomas          #+#    #+#             */
/*   Updated: 2025/08/17 20:00:34 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int is_redir(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<')
            return (1);
		if (input[i] == '>')
			return (1);
		i++;
	}
    return(0);
}

int handle_heredoc(char *input, t_cmd *cmd)
{
    int i;
    int j;
    char *name;

    i = 1;
    if (!input[i])
        return (0);
    while (input[i] == ' ')
            i++;
    j = i;
    if (!input[i] || input[i] == '<' || input[i] == '>')
        return (0);
    while (input[i] != ' ')
        i++;
    name = ft_strndup(input + j, i - j);
    if (cmd->infile != -1)
        close(cmd->infile);
    cmd->infile = -1;
    cmd->here_doc = here_doc(name);
    free(name);
    return (i);
}

int handle_infile(char *input, t_cmd *cmd)
{
    int i;
    int j;
    char *name;

    i = 1;
    if (!input[i])
        return (0);
    if (input[i] == '<')
       i = handle_heredoc(input + i, cmd);
    else
    {   
         while (input[i] == ' ')
            i++;
        j = i;
        if (!input[i] || input[i] == '<' || input[i] == '>')
            return (0);
        while (input[i] != ' ')
            i++;
        name = ft_strndup(input + j, i - j);
        if (cmd->infile != -1)
            close(cmd->infile);
        cmd->infile = open(name, O_WRONLY);
        free(name);
    }
    return (i);
}

int handle_outfile(char *input, t_cmd *cmd)
{
    int i;
    int j;
    char *name;

    i = 1;
    if (!input[i])
        return (0);
    if (input[i] == '<' || input[i] == '>')
        return (0);
    while (input[i] == ' ')
        i++;
    j = i;
    if (!input[i] || input[i] == '<' || input[i] == '>')
        return (0);
    while (input[i] != ' ')
        i++;
    name = ft_strndup(input + j, i - j);
    if (cmd->outfile != -1)
        close(cmd->outfile);
    cmd->outfile = open(name, O_CREAT | O_WRONLY);
    free(name);
    return (i);
}

char *pars_redir(char *input, t_cmd *cmd)
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
                tmp = handle_outfile(input + i + 1, cmd);
                if (!tmp)
                    return (NULL);
                i += tmp;
            }
            else
            {
                tmp = handle_infile(input + i, cmd);
                if (!tmp)
                    return (NULL);
			    i += tmp;
            }
		}
		else if (input[i] == '>')
		{
            tmp = handle_outfile(input + i, cmd);
                if (!tmp)
                    return (NULL);
                i += tmp;
		}
        else
        {
            new_input[j] = input[i];
            j++;
        }
		i++;
	}
    return (new_input);
}
