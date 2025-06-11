/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/11 16:09:22 by authomas         ###   ########lyon.fr   */
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