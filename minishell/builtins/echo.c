/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/01 13:59:47 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../include/data.h"

int		have_flag(char *arg)
{
	size_t	i;
	i = 4;
	while (arg[i])
	{
		if (arg[i] == ' ')
			i++;
		if (arg[i] == '-')
		{
			i++;
			while (arg[i] == 'n')
				i++;
		}
		if (arg[i] != ' ' && arg[i] != '-')
			break ;
	}
	return (i);
}

void	echo(t_cmd cmd)
{
	int		n_flag;
	int		start;
	char	*arg;
	int		n;

	n = 1;
	while (n < cmd.len)
	{
		arg = ft_strjoin(arg, cmd.parts[n].str);
		if (n < cmd.len - 1)
			arg = ft_strjoin(arg, " ");
		n++;
	}
	n_flag = 0;
	start = have_flag(arg);
	write(1, arg+start, ft_strlen(arg + start));
	if (start <= 4)
		write(1, "\n", 1);
}