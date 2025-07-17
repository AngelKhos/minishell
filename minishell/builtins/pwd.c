/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:18:43 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/17 15:16:43 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

void	pwd(t_data *data)
{
	t_env	*env_pwd;
	env_pwd = tree_search(data->env, "PWD");
	if (env_pwd)
		ft_printf("%s\n", env_pwd->data.value);
}