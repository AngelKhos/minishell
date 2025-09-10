/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:14:18 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/10 17:27:33 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"

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

int	export_part_2(t_env *leaf)
{
	if (!leaf->data.key)
		return (free(leaf), 1);
	if (ft_isok(leaf->data.key) == 0)
		return (tree_delete_node(leaf), 1);
	return (0);
}

int	export_core(t_data *data, t_cmd *cmd, int part_i)
{
	t_env	*leaf;
	int		code;

	leaf = env_parse_node(cmd->parts[part_i].str);
	if (!leaf)
		return (1);
	if (!leaf->data.key)
		return (tree_delete_node(leaf), 1);
	code = export_part_2(leaf);
	if (code == 1)
		return (code);
	if (data->env)
		tree_insert(data->env, leaf);
	else
		data->env = leaf;
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int		code;
	int		part_i;

	part_i = 1;
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
