/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/16 15:32:37 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

void	cd(t_data *data, char *cd_args)
{
	chdir(cd_args);
	free(data->curent_path);
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
}