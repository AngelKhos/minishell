/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:18:43 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/08 18:47:21 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

int	pwd(t_data *data)
{
	char	pwd[PATH_MAX];

	(void)data;
	getcwd(pwd, PATH_MAX);
	ft_printf("%s\n", pwd);
	return (0);
}
