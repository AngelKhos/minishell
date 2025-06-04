/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/04 21:01:18 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

void	cd(t_data *data, char *cd_args)
{
	chdir(cd_args);
	free(data->curent_path);
	data->curent_path = malloc(sizeof(char) * PATH_MAX);
	getcwd(data->curent_path, PATH_MAX);
}