/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:14:18 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/09 18:23:14 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"

int	export_part_3(t_cmd *cmd, t_env *leaf, char **val)
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

int	ft_isok(char *str)
{
	char		c;
	size_t		i;

	i = 0;
	if (str[i] && ft_isdigit(str[i]) == 1)
	{
		ft_dprintf(2, "export: '%s': not a valid identifier\n", str);
		return (0);
	}
	while (str[i])
	{
		c = str[i];
		if (c != '_')
		{
			if (ft_isalnum(c) == 0)
			{
				ft_dprintf(2, "export: '%s': not a valid identifier\n", str);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	export_part_2(t_env *leaf, char **val, t_cmd *cmd)
{
	if (!leaf->data.key)
		return (free(leaf), 1);
	if (ft_isok(val[0]) == 0)
		return (free(leaf->data.key), free(leaf), free_array(val), 1);
	leaf->data.value = NULL;
	if (export_part_3(cmd, leaf, val) == 1)
		return (1);
	return (0);
}

int	export_core(t_data *data, t_cmd *cmd, int part_i)
{
	t_env	*leaf;
	char	**val;
	int		code;

	leaf = ft_calloc(sizeof(t_env), 1);
	if (!leaf)
		return (1);
	val = ft_split(cmd->parts[part_i].str, '=');
	if (!val)
		return (free(leaf), 1);
	leaf->data.key = ft_strdup(val[0]);
	if (!leaf->data.key)
		return (free(leaf), free_array(val), 1);
	code = export_part_2(leaf, val, cmd);
	if (code == 1)
		return (code);
	if (data->env)
		tree_insert(data->env, leaf);
	else
		data->env = leaf;
	free_array(val);
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*leaf;
	char	**val;
	int		code;
	int		part_i;

	part_i = 1;
	leaf = NULL;
	val = NULL;
	if (cmd->len == 1)
	{
		print_tree(data->env, 1);
	}
	while (part_i < cmd->len)
	{
		code = export_core(data, cmd, part_i);
		if (code == 1)
			return (code);
		part_i++;
	}
	return (0);
}
