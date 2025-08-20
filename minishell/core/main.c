/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/20 11:39:45 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	g_pid = 0;

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
					display_cmd(data);
					if (!read_cmd(data))
						ft_dprintf(2, "Error: exec error\n");
					free_cmd(data);
				}
			}
			else
				data->exit_code = 0;
			free(data->input);
		}
		else
			exit_minishell_edition(data, NULL);
	}
}

void	increase_shlvl(t_data *data)
{
	int		shlvl;
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
	data->run = 1;
	data->env = envp_to_tree(envp);
	increase_shlvl(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	init_data(data, envp);
	handle_signal();
	handle_readline(data);
	free_data(data);
	rl_clear_history();
	return (data->exit_code);
}
