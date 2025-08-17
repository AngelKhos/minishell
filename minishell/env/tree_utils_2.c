/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:14:31 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/21 12:55:01 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stddef.h>

void	tree_destroy(t_env *root)
{
	if (!root)
		return ;
	tree_destroy(root->left);
	tree_destroy(root->right);
	tree_delete_node(root);
}

void	tree_delete_node(t_env *node)
{
	destroy_data(&node->data);
	free(node);
}

t_env	*tree_insert(t_env *node, t_env *leaf)
{
	t_env	**target;
	int		cmp;

	cmp = ft_strncmp(node->data.key, leaf->data.key, -1);
	if (cmp > 0)
		target = &node->right;
	if (cmp < 0)
		target = &node->left;
	if (cmp != 0)
	{
		if (*target)
			return (tree_insert(*target, leaf));
		*target = leaf;
		return (leaf);
	}
	free(node->data.value);
	node->data.value = leaf->data.value;
	leaf->data.value = NULL;
	tree_destroy(leaf);
	return (node);
}

t_env	*tree_search(t_env *root, char *key)
{
	if (!root)
		return (NULL);
	while (root)
	{
		if (ft_strncmp(root->data.key, key, -1) > 0)
			root = root->right;
		else if (ft_strncmp(root->data.key, key, -1) < 0)
			root = root->left;
		else
			return (root);
	}
	return (NULL);
}

void	destroy_data(t_pair *data)
{
	free(data->key);
	free(data->value);
}
