/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:46:55 by authomas          #+#    #+#             */
/*   Updated: 2025/05/16 01:36:40 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *leaf_from_env(char *envstr)
{
	t_ast *new;
	//char *tmp = ft_strdup(envstr);
	char *adr;
	
	adr = strchr(envstr, '=');
	if (adr)
	{
		new->value = strdup(adr + 1);
		*adr = '\0';
	}
	new->key = strdup(envstr);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast *tree_insert(t_ast *node, t_ast *leaf)
{
	t_ast **target;
	int cmp;

	cmp = ft_strncmp(node->key, leaf->key, -1);
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
	free(node->value);
	node->value = leaf->value;
	leaf->value = NULL;
	tree_destroy(leaf);
	return (node);
}

t_ast *tree_search(t_ast *root, char *key)
{
	if(!root)
		return (NULL);
	while (root)
	{
		if(ft_strncmp(root->key, key, -1) > 0)
			root = root->right;
		else if(ft_strncmp(root->key, key, -1) < 0)
			root = root->left;
		else
			return(root);
	}
	return (NULL);
}

void tree_destroy(t_ast *root)
{
	if (!root)
		return ;
	tree_destroy(root->left);
	tree_destroy(root->right);
	free(root->key);
	free(root->value);
	free(root);
}

t_ast *envp_to_tree(char **envp)
{
	t_ast **root;

	*root = leaf;

}

char **tree_to_envp(t_ast *root)
{
	/* TODO */
}