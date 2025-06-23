/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/23 14:29:55 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	display_cmd(t_data *data)
{
	int	i;
	int c_i;

	i = 0;
	c_i = 0;
	while (c_i < data->nb_pipes + 1)
	{
		i = 0;
		ft_printf("--------------------------- cmd : %i\ncmd len : %i\n", c_i, data->cmd[c_i].len);
		while (i < data->cmd[c_i].len)
		{
			ft_printf("\n--------------\n part : %i\n str : %s\n type : %i\n", i, data->cmd[c_i].parts[i].str, data->cmd[c_i].parts[i].type);
			i++;
		}
		c_i++;
	}
}

void	init_data(t_data *data, char **envp)
{
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
	data->envp = envp;
	data->env = envp_to_tree(envp);
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data, envp);
	handle_signal();
	while (1)
	{
		data->input = readline( "\e[0;35mprompt.png\e[0m>");
		if (data->input)
		{
			if (ft_strlen(data->input) >= 1)
			{
				add_history(data->input);
				if (parsing(data))
				{
					//display_cmd(data);
					read_cmd(data);
					free_cmd(data);
				}
			}
			free(data->input);
		}
		else if (data->input == NULL)
		{
			exit_minishell_edition(data);
		}
	}
	return (EXIT_FAILURE);
}
