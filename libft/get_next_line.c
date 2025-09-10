/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:12:14 by authomas          #+#    #+#             */
/*   Updated: 2025/01/27 16:51:25 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buff[BUFFER_SIZE + 1];
	int			len;

	line = NULL;
	if (buff[0])
		line = ft_strdup_gnl(buff);
	ft_bzero_gnl(buff);
	len = BUFFER_SIZE;
	while (ft_searchline(line) == -1 && len == BUFFER_SIZE)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len <= 0)
			return (free_nl(line, buff, len));
		buff[len] = 0;
		line = ft_join(line, buff);
	}
	if (ft_searchline(line) != -1)
		newline(line, (char *)buff);
	else
		ft_bzero_gnl(buff);
	return (line);
}

void	newline(char *line, char *buff)
{
	char	*tmp;
	size_t	i;

	i = ft_searchline(line) + 1;
	tmp = ft_strdup_gnl(&line[i]);
	while (line[i])
		line[i++] = 0;
	i = 0;
	while (tmp[i])
	{
		buff[i] = tmp[i];
		i++;
	}
	buff[i] = 0;
	free(tmp);
}

char	*free_nl(char *line, char *buff, int i)
{
	if (i == -1)
	{
		free(line);
		return (NULL);
	}
	ft_bzero_gnl(buff);
	return (line);
}
