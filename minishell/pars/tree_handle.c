/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:46:55 by authomas          #+#    #+#             */
/*   Updated: 2025/07/21 12:50:11 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stddef.h>

int	env_parse_str(char *envstr, t_pair *out)
{
	char	*adr;

	out->key = NULL;
	out->value = NULL;
	adr = ft_strchr(envstr, '=');
	if (adr)
	{
		out->value = ft_strdup(adr + 1);
		if (out->value == NULL)
		{
			destroy_data(out);
			return (1);
		}
		*adr = '\0';
	}
	out->key = ft_strdup(envstr);
	if (out->key == NULL)
	{
		destroy_data(out);
		return (1);
	}
	return (0);
}

t_env	*env_parse_node(char *envstr)
{
	t_env	*new;
	t_pair	kv;

	if (env_parse_str(envstr, &kv))
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->data = kv;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	tree_remove_part_2(t_env **root, t_env *new_node, t_env *insert)
{
	if (!(*root)->left && !(*root)->right)
	{
		tree_delete_node(*root);
		*root = NULL;
	}
	else if ((*root)->left && !(*root)->right)
	{
		new_node = (*root)->left;
		tree_delete_node(*root);
		*root = new_node;
	}
	else if (!(*root)->left && (*root)->right)
	{
		new_node = (*root)->right;
		tree_delete_node(*root);
		*root = new_node;
	}
	else if ((*root)->left && (*root)->right)
	{
		new_node = (*root)->left;
		insert = (*root)->right;
		tree_delete_node(*root);
		*root = new_node;
		tree_insert(*root, insert);
	}
}

void	tree_remove(t_env **root, char *key)
{
	t_env	*new_node;
	t_env	*insert;

	new_node = NULL;
	insert = NULL;
	if (!root)
		return ;
	if (ft_strncmp((*root)->data.key, key, -1) != 0)
	{
		if ((*root)->left)
			tree_remove(&(*root)->left, key);
		if ((*root)->right)
			tree_remove(&(*root)->right, key);
	}
	else
	{
		tree_remove_part_2(root, new_node, insert);
	}
}
