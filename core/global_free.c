/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:58:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/14 14:58:26 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	double_free(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
}

void	free_array(char **array)
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
}
