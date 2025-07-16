/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/23 15:19:29 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>

int		here_doc(t_data *data, char *word)
{
	(void)data;
	int		hd_fd;
	char	*here_doc_input;

	hd_fd = open(".here_doc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	here_doc_input = NULL;
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
	hd_fd = open(".here_doc.tmp", O_RDONLY);
	return (hd_fd);
}
