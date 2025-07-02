/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/02 16:43:49 by authomas         ###   ########lyon.fr   */
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
	start = have_flag(arg);
	write(1, arg+start, ft_strlen(arg + start));
	if (start <= 4)
		write(1, "\n", 1);
}