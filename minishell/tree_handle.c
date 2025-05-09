/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:46:55 by authomas          #+#    #+#             */
/*   Updated: 2025/05/09 16:55:08 by authomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printenv(char **envp)
{
	for (size_t i = 0; envp[i]; i++)
	{
		printf("%s\n", envp[i]);
	}
}

t_ast *tree_from_env(char *envstr)
{
	t_ast *new;
	char *adr;
	
	adr = strchr(envstr, '=');
	if (adr)
	{
		new->value = strdup(adr + 1);
		*adr = '\0';
	}
	new->key = strdup(str);
	new->left = NULL;
	new->right = NULL;
}

t_ast *tree_insert(t_ast *node, t_ast *leaf)
{
	/* TODO, recursive */
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
}

void tree_destroy(t_ast *root)
{
	if (!root)
		return ;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root->key);
	free(root->value);
	free(root);
}

char **tree_to_envp(t_ast *root)
{
	/* TODO */
}

int main(int argc, char **argv, char **envp)
{
	
	printenv(envp);
	return (0);
}