/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 13:56:54 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	handle_readline(t_data *data)
{
	char *prompt;

	prompt = NULL;
	while (data->run)
	{
		prompt = get_prompt(data);
		data->input = readline(prompt);
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
			free(prompt);
		}
		else
			exit_minishell_edition(data, "exit");
	}
}

void	increase_shlvl(t_data *data)
{
	int	shlvl;
	t_env	*var_shlvl;
	char	*val;

	var_shlvl = tree_search(data->env, "SHLVL");
	if (var_shlvl && var_shlvl->data.value)
	{
		shlvl = ft_atoi(var_shlvl->data.value);
		shlvl++;
		val = ft_itoa(shlvl);
		if (val)
		{
			free(var_shlvl->data.value);
			var_shlvl->data.value = val;
		}
		
	}
}

void	init_data(t_data *data, char **envp)
{
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
	data->run = 1;
	data->env = envp_to_tree(envp);
	increase_shlvl(data);
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
