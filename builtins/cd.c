/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/25 16:03:14 by gchauvet         ###   ########.fr       */
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

void	update_oldpwd(t_data *data)
{
	t_env	*env_oldpwd;
	char	*tmp;
	char	oldpwd[PATH_MAX];

	env_oldpwd = tree_search(data->env, "OLDPWD");
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		oldpwd[0] = '\0';
	if (env_oldpwd)
	{
		tmp = ft_strdup(oldpwd);
		if (tmp)
		{
			if (env_oldpwd->data.value)
				free(env_oldpwd->data.value);
			env_oldpwd->data.value = tmp;
		}
	}
}

void	update_pwd(t_data *data)
{
	t_env	*env_pwd;
	char	*tmp;
	char	pwd[PATH_MAX];

	env_pwd = tree_search(data->env, "PWD");
	if (getcwd(pwd, PATH_MAX) == NULL)
		pwd[0] = '\0';
	if (env_pwd)
	{
		tmp = ft_strdup(pwd);
		if (tmp)
		{
			if (env_pwd->data.value)
				free(env_pwd->data.value);
			env_pwd->data.value = tmp;
		}
	}
}

void	cd_body(t_data *data, t_cmd cmd, int *code)
{
	update_oldpwd(data);
	*code = change_dir(data, cmd);
	update_pwd(data);
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
