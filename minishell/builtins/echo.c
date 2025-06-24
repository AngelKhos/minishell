/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/24 18:04:04 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

int		have_flag(char *arg, int *flag)
{
	size_t	i;

	flag = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-')
		{
			i++;
			if (arg[i] == 'n')
				*flag = 1;
			i++;
			if (arg[i] != 'n' && arg[i] != ' ')
				*flag = 0;
		}
		if (arg[i] == ' ')
			i++;
		if (arg[i] != ' ' && arg[i] != '-')
		{
			break ;
		}
		i++;
	}
	return (i);
}

void	echo(char *arg)
{
	int n_flag;
	int start;

	n_flag = 0;
	start = have_flag(arg, &n_flag);
	write(1, arg+start, ft_strlen(arg + start));
	if (!n_flag)
		write(1, "\n", 1);
}