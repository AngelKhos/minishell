/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/13 23:01:14 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	write_in_here_doc(int hd_fd, char *here_doc_input)
{
	write(hd_fd, here_doc_input, ft_strlen(here_doc_input));
	write(hd_fd, "\n", 1);
}

int	here_doc(char *word, t_data *data)
{
	int		hd_fd;
	char	*here_doc_input;

	(void)data;
	hd_fd = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == -1)
		return (-1);
	here_doc_input = NULL;
	while (1)
	{
		signal(SIGINT, hd_sigint_handle);
		rl_catch_signals = 1;
		rl_event_hook = rl_hook_event_handler; 
		here_doc_input = readline(">");
		if (ft_strncmp(here_doc_input, word, -1) == 0)
			break ;
		if (here_doc_input)
		{
			if (g_sig_val == 130)
			{
				data->exit_code = 130;
				g_sig_val = 0;
				break;
			}
			write_in_here_doc(hd_fd, here_doc_input);
		}
		else
		{
			write(1, "\n", 1);
			break ;
		}
		free(here_doc_input);
	}
	rl_catch_signals = 0;
	rl_event_hook = NULL;
	close(hd_fd);
	hd_fd = open(word, O_RDONLY);
	return (free(here_doc_input), hd_fd);
}
