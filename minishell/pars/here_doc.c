/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/02 16:19:20 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void	sigint_handle_hd(int code)
{
	(void)code;
	exit(130);
}

int	here_doc(char *word, t_data *data)
{
	int		hd_fd;
	char	*here_doc_input;
	int		code;

	hd_fd = open(word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	here_doc_input = NULL;
	g_pid = fork();
	if (g_pid == 0)
	{
		signal(SIGINT, &sigint_handle_hd);
		while (ft_strncmp(here_doc_input, word, -1) != 0)
		{
			if (here_doc_input)
			{
				write(hd_fd, here_doc_input, ft_strlen(here_doc_input));
				write(hd_fd, "\n", 1);
			}
			here_doc_input = readline(">");
		}
		close(hd_fd);
		exit(0);
	}
	waitpid(g_pid, &code, 0);
	data->exit_code = code >> 8;
	close(hd_fd);
	hd_fd = open(word, O_RDONLY);
	return (hd_fd);
}
