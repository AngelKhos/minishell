/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:14:18 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/29 10:43:08 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"

void	print_export_env(t_env *root)
{
	if (root == NULL)
		return ;
	if (root->data.value)
		ft_printf("export %s=%s\n", root->data.key, root->data.value);
	print_export_env(root->right);
	print_export_env(root->left);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_env	*leaf;
	char	**val;

	leaf = NULL;
	val = NULL;
	if (cmd->len > 1)
	{
		if (ft_strchr(cmd->parts[1].str, '=') == 0)
			return (0);
		leaf = ft_calloc(sizeof(t_env), 1);
		if (!leaf)
			return (0);
		val = ft_split(cmd->parts[1].str, '=');
		if (!val)
			return (free(leaf), 0);
		leaf->data.key = ft_strdup(val[0]);
		leaf->data.value = ft_strdup(val[1]);
		tree_insert(data->env, leaf);
		free_array(val);
	}
	else
		print_export_env(data->env);
	return (0);
}
