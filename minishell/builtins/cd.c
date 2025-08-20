/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/08/20 11:05:51 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

int	change_dir(t_data *data, t_cmd cmd)
{
	t_env	*home;

	if (cmd.len == 1)
	{
		home = tree_search(data->env, "HOME");
		if (!home)
		{
			ft_dprintf(2, "\e[1;37mcd\e[0m: HOME not set\n");
			return (1);
		}
		chdir(home->data.value);
	}
	else
	{
		if (chdir(cmd.parts[1].str) != 0)
		{
			ft_dprintf(2,
				"\e[1;37mcd\e[0m: %s\e[0m: No such file or directory\n",
				cmd.parts[1].str);
			return (1);
		}
	}
	return (0);
}

void	cd_body(t_data *data, t_cmd cmd, int *code)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	pwd[PATH_MAX];

	env_oldpwd = tree_search(data->env, "OLDPWD");
	if (env_oldpwd)
	{
		if (env_oldpwd->data.value)
			free(env_oldpwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_oldpwd->data.value = ft_strdup(pwd);
	}
	*code = change_dir(data, cmd);
	env_pwd = tree_search(data->env, "PWD");
	if (env_pwd)
	{
		if (env_pwd->data.value)
			free(env_pwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_pwd->data.value = ft_strdup(pwd);
	}
}

int	cd(t_data *data, t_cmd cmd)
{
	int		code;

	code = 0;
	if (cmd.len > 2)
	{
		ft_dprintf(2, "\e[1;37mcd\e[0m: too many arguments\n");
		return (1);
	}
	cd_body(data, cmd, &code);
	return (code);
}
