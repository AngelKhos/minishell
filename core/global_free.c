/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:58:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/30 19:09:18 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

int	double_free(void *ptr1, void *ptr2, int ret)
{
	free(ptr1);
	free(ptr2);
	return (ret);
}

void	*double_free_ptr(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
	return (NULL);
}

int	free_array(char **array, int ret)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (ret);
}

int	spe_free(t_data *data, char **envp)
{
	free_cmd(data);
	free_data(data);
	free_array(envp, 0);
	return (0);
}

int	free_more(void *to_free, char **array, int ret)
{
	free(to_free);
	free_array(array, 0);
	return (ret);
}
