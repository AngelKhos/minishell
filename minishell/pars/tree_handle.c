/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:46:55 by authomas          #+#    #+#             */
/*   Updated: 2025/05/31 09:24:36 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int env_parse_str(char *envstr, t_pair *out)
{
	
	char *adr;
	
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
	return 0;
}

void destroy_data(t_pair *data)
{
	free(data->key);
	free(data->value);
}

t_env *env_parse_node(char *envstr)
{
	t_env *new;
	t_pair kv;

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

t_env *tree_insert(t_env *node, t_env *leaf)
{
	t_env **target;
	int cmp;

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

t_env *tree_search(t_env *root, char *key)
{
	if(!root)
		return (NULL);
	while (root)
	{
		if(ft_strncmp(root->data.key, key, -1) > 0)
			root = root->right;
		else if(ft_strncmp(root->data.key, key, -1) < 0)
			root = root->left;
		else
			return(root);
	}
	return (NULL);
}

void tree_destroy(t_env *root)
{
	if (!root)
		return ;
	tree_destroy(root->left);
	tree_destroy(root->right);
	tree_delete_node(root);
}

void tree_delete_node(t_env *node)
{
	destroy_data(&node->data);
	free(node);
}

void tree_remove(t_env **root, char *key)
{
	t_env *new_node;
	t_env *insert;

	new_node = NULL;
	insert = NULL;
	if(!root)
	return ;
	if (ft_strncmp((*root)->data.key, key, -1) != 0)
	{
		tree_remove(&(*root)->left, key);
		tree_remove(&(*root)->right, key);
	}
	else
	{
		if(!(*root)->left && !(*root)->right)
		{
			tree_delete_node(*root);
			*root = NULL;
		}
		else if((*root)->left && !(*root)->right)
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
}

t_env *envp_to_tree(char **envp)
{
	t_env *root;
	t_env *leaf;
	int i;

	root = env_parse_node(envp[0]);
	i = 1;
	while (envp[i])
	{
		leaf = env_parse_node(envp[i]);
		tree_insert(root, leaf);
		i++;
	}
	return (root);
}

// char **tree_to_envp(t_env *root)
// {
// 	/* TODO */
// }

void print_tree(t_env *root)
{
	if (root == NULL)
        return;
	ft_printf("%s = %s\n", root->data.key, root->data.value);
	print_tree(root->right);
    print_tree(root->left);
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env *uwu = envp_to_tree(envp);
	tree_remove(&uwu, "USER");
	print_tree(uwu);
	tree_destroy(uwu);
	return (0);
}