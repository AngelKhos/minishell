/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:58:45 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 13:13:37 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include <stdlib.h>
#include <unistd.h>

size_t	get_promp_size(t_data *data, char *const_str)
{
	size_t	pr_size;
	t_env	*home;
	t_env	*path;

	home = NULL;
	path = NULL;
	pr_size = 0;
	pr_size = ft_strlen(const_str);
	path = tree_search(data->env, "PWD");
	home = tree_search(data->env, "HOME");
	if (home)
	{
		if (path && path->data.value)
			pr_size += (ft_strlen(path->data.value) - ft_strlen(home->data.value)) + 1;
	}
	else
	{
		if (path && path->data.value)
			pr_size += (ft_strlen(path->data.value));
	
	}
	return (pr_size);
}

void    prompt_if(char *prompt, t_env *path, t_env *home)
{
    if (path)
	{
		if (home)
			ft_memcpy(prompt, "╔\e[0;105m ~", ft_strlen("╔\e[0;105m ~"));
		if (!home)
			ft_memcpy(prompt, "╔\e[0;105m ", ft_strlen("╔\e[0;105m "));
		if (home)
			ft_memcpy(prompt+ft_strlen("╔\e[0;105m ~"), path->data.value + ft_strlen(home->data.value), ft_strlen(path->data.value) - ft_strlen(home->data.value));
		if (!home)
			ft_memcpy(prompt+ft_strlen("╔\e[0;105m "), path->data.value, ft_strlen(path->data.value));
	}
}

//C = color
char	*get_prompt(t_data *data)
{
	t_env	*path;
	char *prompt;
	t_env	*home;
	size_t	pr_size;

	home = NULL;
	pr_size = get_promp_size(data,
        "╔\e[0;105m  \e[0;107m     \e[0m▓▓▒░\n╚══");
	prompt = ft_calloc(pr_size + 1, 1);
	path = tree_search(data->env, "PWD");
    home = tree_search(data->env, "HOME");
    prompt_if(prompt, path, home);
	ft_memcpy(prompt + (pr_size - ft_strlen(" \e[0;107m     \e[0m▓▓▒░\n╚══")),
        " \e[0;107m     \e[0m▓▓▒░\n╚══",
        ft_strlen(" \e[0;107m     \e[0m▓▓▒░\n╚══"));
	return (prompt);
}
