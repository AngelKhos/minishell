/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:40:46 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/24 14:43:38 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <stdlib.h>

void free_data(t_data *data)
{
    if (data->curent_path)
        free(data->curent_path);
}