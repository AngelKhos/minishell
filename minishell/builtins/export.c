/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:14:18 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/21 14:31:38 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"

void	ft_export(t_data *data, char *arg)
{
	t_env	*leaf;
	char	**val;

	leaf = NULL;
	val = NULL;
	if (ft_strchr(arg, '=') == 0)
		return ;
	leaf = ft_calloc(sizeof(t_env), 1);
	if (!leaf)
		return ;
	val = ft_split(arg, '=');
	if (!val)
		return (free(leaf));
	leaf->data.key = ft_strdup(val[0]);
	leaf->data.value = ft_strdup(val[1]);
	tree_insert(data->env, leaf);
	free_array(val);
}
