/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:15:07 by ********          #+#    #+#             */
/*   Updated: 2025/01/26 10:53:12 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero_gnl(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *) s = 0;
		s++;
		i++;
	}
}

void	ft_next_line(char *buffer)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return ;
	else if (buffer[i] == '\n')
	{
		len = (ft_strlen_gnl(buffer) - i);
		while (j < len)
		{
			buffer[j] = buffer[i + 1];
			i++;
			j++;
		}
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	int			nb_read;
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	nb_read = 1;
	line = ft_strdup_gnl("");
	if (!line)
		return (NULL);
	while (nb_read)
	{
		line = ft_strjoin(line, (const char *)buffer);
		if (ft_strchr(line, '\n'))
			break ;
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read < 0)
			return (free(line), ft_bzero_gnl(buffer, BUFFER_SIZE), NULL);
		if (nb_read == 0 && buffer[0] == 0)
			return (free(line), NULL);
		buffer[nb_read] = '\0';
	}
	ft_next_line(buffer);
	return (line);
}
