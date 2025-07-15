/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:28:34 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/14 16:33:44 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <unistd.h>

void	display_cmd(t_data *data)
{
	int	i;
	int c_i;

	i = 0;
	c_i = 0;
	while (c_i < data->nb_pipes + 1)
	{
		i = 0;
		ft_printf("--------------------------- cmd : %i\ncmd len : %i\n", c_i, data->cmd[c_i].len);
		while (i < data->cmd[c_i].len)
		{
			ft_printf("\n--------------\n part : %i\n str : %s\n type : %i\n", i, data->cmd[c_i].parts[i].str, data->cmd[c_i].parts[i].type);
			i++;
		}
		c_i++;
	}
}

void print_char_array(char **array)
{
    size_t i;

    i = 0;
    while (array[i])
    {
        ft_printf("%s\n", array[i]);
        i++;
    }
}