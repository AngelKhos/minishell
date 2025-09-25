/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/25 14:48:24 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	g_sig_val = 0;

void	readline_loop(t_data *data)
{
	if (ft_strlen(data->input) >= 1)
	{
		add_history(data->input);
		if (parsing(data))
		{
			if (g_sig_val != 130)
				if (!read_cmd(data))
					ft_dprintf(2, "Error: exec error\n");
			close_file(data);
			free_cmd(data);
		}
	}
	free(data->input);
}

void	handle_readline(t_data *data)
{
	while (data->run)
	{
		handle_signal();
		data->input = readline("(つ ╹╹)つ──☆*:");
		if (g_sig_val)
			data->exit_code = g_sig_val;
		g_sig_val = 0;
		signal(SIGINT, exec_sigint_handle);
		if (data->input)
		{
			readline_loop(data);
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
	data->pid = 0;
	data->exit_code = 0;
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
	{
		free_data(data);
		return (EXIT_FAILURE);
	}
	handle_readline(data);
	code = data->exit_code;
	free_data(data);
	rl_clear_history();
	return (code);
}
