/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/29 15:34:58 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	write_in_here_doc(int hd_fd, char *here_doc_input, t_data *data)
{
	pars_exp(data, &here_doc_input);
	write(hd_fd, here_doc_input, ft_strlen(here_doc_input));
	write(hd_fd, "\n", 1);
	free(here_doc_input);
}

int	heredoc_loop(char *here_doc_input, char *word, int hd_fd, t_data *data)
{
	free(here_doc_input);
	here_doc_input = readline(">");
	if (ft_strncmp(here_doc_input, word, -1) == 0)
	{
		free(here_doc_input);
		here_doc_input = NULL;
		return (0);
	}
	if (here_doc_input)
	{
		if (g_sig_val == 130)
		{
			free(here_doc_input);
			return (0);
		}
		write_in_here_doc(hd_fd, here_doc_input, data);
		here_doc_input = NULL;
	}
	else
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

char	*rand_name(char *word)
{
	static int	i = 0;
	char		*name;
	char		*tmp;

	i++;
	tmp = ft_itoa(i);
	if (!tmp)
		return (NULL);
	(void)word;
	name = ft_strjoin(tmp, word);
	free(tmp);
	if (!name)
		return (NULL);
	return (name);
}

int	here_doc(char *word, char **hd_name, t_data *data)
{
	int		hd_fd;
	char	*here_doc_input;
	char	*file_name;

	file_name = rand_name(word);
	if (!file_name)
		return (double_free(NULL, word, -1));
	hd_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == -1)
	{
		free(file_name);
		return (double_free(*hd_name, word, -1));
	}
	here_doc_input = NULL;
	signal(SIGINT, hd_sigint_handle);
	rl_event_hook = rl_hook_event_handler;
	while (1)
		if (!heredoc_loop(here_doc_input, word, hd_fd, data))
			break ;
	rl_event_hook = NULL;
	signal(SIGINT, exec_sigint_handle);
	close(hd_fd);
	hd_fd = open(file_name, O_RDONLY);
	*hd_name = file_name;
	return (double_free(word, here_doc_input, hd_fd));
}
