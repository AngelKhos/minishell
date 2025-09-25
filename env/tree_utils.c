/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:44:57 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/25 16:13:51 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stddef.h>

t_env	*envp_to_tree(char **envp)
{
	t_env	*root;
	t_env	*leaf;
	int		i;

	root = env_parse_node(envp[0]);
	i = 1;
	while (envp[i])
	{
		leaf = env_parse_node(envp[i]);
		if (!leaf)
			return (NULL);
		tree_insert(root, leaf);
		i++;
	}
	return (root);
}

size_t	tree_get_len(t_env *root)
{
	size_t	s;

	s = 0;
	if (root)
	{
		s++;
		if (root->left)
			s += tree_get_len(root->left);
		if (root->right)
			s += tree_get_len(root->right);
	}
	return (s);
}

void	get_str_key_va(size_t *i, char **envp, t_env *root)
{
	char	*str;
	char	*key;
	char	*keyplus;

	if (!root)
		return ;
	(*i)++;
	key = ft_strdup(root->data.key);
	if (!key)
		return ;
	keyplus = ft_strjoin(key, "=");
	free(key);
	if (!keyplus)
		return ;
	str = ft_strjoin(keyplus, root->data.value);
	free(keyplus);
	if (!str)
		return ;
	envp[(*i)] = str;
	get_str_key_va(i, envp, root->right);
	get_str_key_va(i, envp, root->left);
}

char	**tree_to_envp(t_env *root)
{
	char	**envp;
	size_t	len;
	size_t	i;

	i = -1;
	len = tree_get_len(root);
	envp = ft_calloc(sizeof(char *), len + 1);
	if (!envp)
		return (NULL);
	get_str_key_va(&i, envp, root);
	return (envp);
}

void	print_tree(t_env *root, int ex)
{
	if (root == NULL)
		return ;
	if (ex == 0)
	{
		if (root->data.value && root->data.value[0] != '\0')
			ft_printf("%s=%s\n", root->data.key, root->data.value);
	}
	else
	{
		if (root->data.value)
		{
			ft_printf("export %s=\"%s\"\n", root->data.key, root->data.value);
		}
		else
			ft_printf("export %s\n", root->data.key);
	}
	print_tree(root->right, ex);
	print_tree(root->left, ex);
}
