/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:44:57 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/23 13:42:25 by authomas         ###   ########lyon.fr   */
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

	if (!root)
		return ;
	(*i)++;
	str = ft_strdup(root->data.key);
	if (!str)
		return ;
	str = ft_strjoin(str, "=");
	if (!str)
		return ;
	str = ft_strjoin(str, root->data.value);
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
	get_str_key_va(&i, envp, root);
	return (envp);
}

void	print_tree(t_env *root)
{
	if (root == NULL)
		return ;
	if (root->data.value)
		ft_printf("%s=%s\n", root->data.key, root->data.value);
	print_tree(root->right);
	print_tree(root->left);
}
