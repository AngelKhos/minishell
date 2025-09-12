/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/12 18:20:01 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

t_pid_code	g_pid;

void	handle_readline(t_data *data)
{
	while (data->run)
	{
		handle_signal();
		data->input = readline("\e[0;35m(つ ╹╹)つ\e[0;91m──\e[0;33m☆*:\e[0m");
		if (data->input)
		{
			if (ft_strlen(data->input) >= 1)
			{
				add_history(data->input);
				if (parsing(data))
				{
					if (!read_cmd(data))
						ft_dprintf(2, "Error: exec error\n");
					close_file(data);
					free_cmd(data);
				}
			}
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

int	init_data(t_data *data, char **envp)
{
	g_pid.pid = 0;
	g_pid.exit_code = 0;
	data->run = 1;
	if (*envp)
		data->env = envp_to_tree(envp);
	if (!init_default_env(data))
		return (0);
	increase_shlvl(data);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		code;

	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (EXIT_FAILURE);
	if (!init_data(data, envp))
		return (free_data(data), EXIT_FAILURE);
	handle_readline(data);
	code = g_pid.exit_code;
	free_data(data);
	rl_clear_history();
	return (code);
}
