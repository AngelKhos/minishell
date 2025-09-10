/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:30 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 14:02:14 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/data.h"

int	check_flag(t_cmd cmd, int *n)
{
	int	i;
	int	flag;

	flag = 0;
	while (*n < cmd.len && cmd.parts[*n].str[0] == '-')
	{
		i = 1;
		flag = 1;
		while (cmd.parts[*n].str[i] == 'n')
			i++;
		if (!cmd.parts[*n].str[i])
			(*n)++;
		else
		{
			flag = 0;
			return (flag);
		}
	}
	return (flag);
}

int	echo(t_cmd cmd)
{
	int	n;
	int	flag;

	n = 1;
	flag = check_flag(cmd, &n);
	while (n < cmd.len)
	{
		ft_printf(cmd.parts[n].str);
		if (n != cmd.len - 1)
			ft_printf(" ");
		n++;
	}
	if (cmd.len <= 1 || !flag)
		ft_printf("\n");
	return (0);
}
