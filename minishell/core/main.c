/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/02 16:28:52 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/data.h"
#include <linux/limits.h>
#include <readline/chardefs.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

void	fake_parsing(t_data *data)
{
	size_t	size;
	size_t	i;
	char	**cmd_str;

	size = 0;
	i = 0;
	cmd_str = ft_split(data->input, ' ');
	i = 0;
	while (cmd_str[size])
		size++;
	data->cmd->parts = ft_calloc(sizeof(t_part), size);
	data->cmd->len = size;
	while (cmd_str[i])
	{
		data->cmd->parts[i].str = ft_strdup(cmd_str[i]);
		if (i <= 0)
		{
			data->cmd->parts[i].type = CMD;
		}
		else
			data->cmd->parts[i].type = ARG;
		i++;
	}
}

void	display_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->cmd->len)
	{
		ft_printf("\n--------------\n part : %i\n str : %s\n type : %i", i, data->cmd->parts[i].str, data->cmd->parts[i].type);
		i++;
	}
}

void	init_data(t_data *data, char **envp)
{
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
	data->cmd = malloc(sizeof(t_cmd));
	data->envp = envp;
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data, envp);
	while (1)
	{
		data->input = ft_strdup(readline("prompt.png>"));
		if (data->input)
		{
			if (ft_strlen(data->input) >= 1)
			{
				add_history(data->input);
				fake_parsing(data);
				read_cmd(data, data->cmd);
				ft_printf("\n");
			}
			if (ft_strncmp(data->input, "exit", -1) == 0)
			{
				exit_minishell_edition(data);
			}
			free(data->input);
		}
	}
	return (EXIT_FAILURE);
}
