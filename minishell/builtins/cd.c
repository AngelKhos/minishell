/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/21 16:22:06 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

void	changer_dir(t_data *data, t_cmd cmd)
{
	t_env	*home;

	if (cmd.len == 1)
	{
		home = tree_search(data->env, "HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		chdir(home->data.value);
	}
	else
	{
		if (chdir(cmd.parts[1].str) != 0)
			ft_printf("cd: %s: No such file or directory\n", cmd.parts[1].str);
	}
}

void	cd(t_data *data, t_cmd cmd)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	pwd[PATH_MAX];

	if (cmd.len > 2)
	{
		ft_printf("cd: too many arguments\n");
		return ;
	}
	env_oldpwd = tree_search(data->env, "OLDPWD");
	if (env_oldpwd)
	{
		free(env_oldpwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_oldpwd->data.value = ft_strdup(pwd);
	}
	changer_dir(data, cmd);
	env_pwd = tree_search(data->env, "PWD");
	if (env_pwd)
	{
		free(env_pwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_pwd->data.value = ft_strdup(pwd);
	}
}
