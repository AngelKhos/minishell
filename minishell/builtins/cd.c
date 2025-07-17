/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:54 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/17 16:20:23 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <linux/limits.h>

void	cd(t_data *data, char *cd_args)
{
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	char	pwd[PATH_MAX];

	env_oldpwd = tree_search(data->env, "OLDPWD");
	if (env_oldpwd)
	{
		free(env_oldpwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_oldpwd->data.value = ft_strdup(pwd);
	}
	env_pwd = tree_search(data->env, "PWD");
	chdir(cd_args);
	if (env_pwd)
	{
		free(env_pwd->data.value);
		getcwd(pwd, PATH_MAX);
		env_pwd->data.value = ft_strdup(pwd);
	}
}

// todo: cd sans args fais ouvrire le home via la var env HOME
//				Si HOME est unset 'bash: cd: HOME not set'
// check si le chdir pete (entrer dans test/test/. et rm ../../test ou un fichier qui existe pas) juste pas cracher