/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/17 16:35:24 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <unistd.h>

void	handle_readline(t_data *data)
{
	while (data->run)
	{
		data->input = readline("\e[0;35m(つ ╹╹)つ\e[0;91m──\e[0;33m☆*:・ﾟ\e[0m$");
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
		else
			exit_minishell_edition(data, "exit");
	}
}

void	init_data(t_data *data, char **envp)
{
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
	data->run = 1;
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
	//print_char_array(tree_to_envp(data->env));
	handle_readline(data);
	free_data(data);
	return (EXIT_SUCCESS);
}
