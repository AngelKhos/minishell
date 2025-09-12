/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/12 18:38:50 by gchauvet         ###   ########.fr       */
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
		here_doc_input = readline(">");
		if (ft_strncmp(here_doc_input, word, -1) == 0)
			break ;
		if (here_doc_input)
			write_in_here_doc(hd_fd, here_doc_input);
		else
		{
			write(1, "\n", 1);
			break ;
		}
		free(here_doc_input);
	}
	close(hd_fd);
	hd_fd = open(word, O_RDONLY);
	return (free(here_doc_input), hd_fd);
}
