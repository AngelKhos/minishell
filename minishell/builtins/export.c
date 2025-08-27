/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:14:18 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/27 13:43:16 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"

int	export_part_2(t_cmd *cmd, t_env *leaf, char **val)
{
	if (val[1])
	{
		leaf->data.value = ft_strdup(val[1]);
		if (!leaf->data.value)
			return (free(leaf->data.value), free(leaf), 1);
	}
	else if (ft_strchr(cmd->parts[1].str, '='))
	{
		leaf->data.value = ft_strdup("");
		if (!leaf->data.value)
			return (free(leaf->data.value), free(leaf), 1);
	}
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*leaf;
	char	**val;

	leaf = NULL;
	val = NULL;
	if (cmd->len > 1)
	{
		leaf = ft_calloc(sizeof(t_env), 1);
		if (!leaf)
			return (1);
		val = ft_split(cmd->parts[1].str, '=');
		if (!val)
			return (free(leaf), 1);
		leaf->data.key = ft_strdup(val[0]);
		if (!leaf->data.key)
			return (free(leaf), 1);
		leaf->data.value = NULL;
		if (export_part_2(cmd, leaf, val) == 1)
			return (1);
		tree_insert(data->env, leaf);
		free_array(val);
	}
	else
		print_tree(data->env, 1);
	return (0);
}
