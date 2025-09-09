/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:56:56 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/09 17:03:38 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

void	add_to_env(t_data *data, t_env *leaf)
{
	if (!data->env)
		data->env = leaf;
	else
		tree_insert(data->env, leaf);
}

int	alloc_oldpwd(t_data *data, t_env *oldpwd)
{
	if (!tree_search(data->env, "OLDPWD"))
	{
		oldpwd = ft_calloc(sizeof(t_env), 1);
		if (!oldpwd)
			return (tree_remove(&data->env, "SHLVL"),
				tree_remove(&data->env, "PWD"), 0);
		oldpwd->data.key = ft_strdup("OLDPWD");
		if (!oldpwd->data.key)
			return (tree_remove(&data->env, "SHLVL"),
				tree_remove(&data->env, "PWD"), 0);
		oldpwd->data.value = NULL;
		add_to_env(data, oldpwd);
	}
	return (1);
}

int	alloc_pwd(t_data *data, t_env *pwd)
{
	if (!tree_search(data->env, "PWD"))
	{
		pwd = ft_calloc(sizeof(t_env), 1);
		if (!pwd)
			return (tree_remove(&data->env, "SHLVL"),
				tree_remove(&data->env, "PWD"), 0);
		pwd->data.key = ft_strdup("PWD");
		if (!pwd->data.key)
			return (tree_remove(&data->env, "SHLVL"), 0);
		pwd->data.value = NULL;
		add_to_env(data, pwd);
	}
	return (1);
}

int	init_default_env(t_data *data)
{
	t_env	*pwd;
	t_env	*oldpwd;
	t_env	*shlvl;

	pwd = NULL;
	oldpwd = NULL;
	if (!tree_search(data->env, "SHLVL"))
	{
		shlvl = ft_calloc(sizeof(t_env), 1);
		shlvl->data.key = ft_strdup("SHLVL");
		if (!shlvl->data.key)
			return (0);
		shlvl->data.value = ft_strdup("1");
		if (!shlvl->data.value)
			return (free(shlvl->data.key), 0);
		add_to_env(data, shlvl);
	}
	if (alloc_pwd(data, pwd) == 0)
		return (0);
	if (alloc_oldpwd(data, oldpwd) == 0)
		return (0);
	return (1);
}
