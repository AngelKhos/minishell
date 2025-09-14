/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:57:57 by authomas          #+#    #+#             */
/*   Updated: 2025/09/14 16:25:49 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char	*get_expand(char *key_src, int key_size, t_data *data)
{
	char	*key;
	t_env	*root;
	char	*name;

	if (key_src[1] == '?')
	{
		name = ft_itoa(data->exit_code);
		if (!name)
			return (NULL);
		return (name);
	}
	key = ft_strndup(key_src + 1, key_size - 1);
	if (!key)
		return (NULL);
	root = tree_search(data->env, key);
	free(key);
	if (!root)
		return (NULL);
	name = ft_strdup(root->data.value);
	if (!name)
		return (NULL);
	return (name);
}

char	*make_expand(char *token, char *value, int key_len)
{
	char	*new_token;
	int		i[2];
	int		value_len;

	i[0] = 0;
	i[1] = 0;
	value_len = key_len;
	if (value)
		value_len = ft_strlen(value);
	new_token = ft_calloc(sizeof(char), ft_strlen(token) + value_len);
	if (!new_token)
		return (NULL);
	while (token[i[0]] && token[i[0]] != '$')
		new_token[i[1]++] = token[i[0]++];
	if (!value)
		ft_strlcpy(new_token + i[1], token + i[0] + key_len,
			ft_strlen(token) - i[0] + 1);
	else
	{
		ft_strlcat(new_token, value, ft_strlen(new_token) + value_len + 1);
		i[1] += value_len;
		i[0] += key_len;
		ft_strlcpy(new_token + i[1], token + i[0], ft_strlen(token) - i[0] + 1);
	}
	return (free(token), new_token);
}

int	pars_exp_loop(t_data *data, char **raw_cmd, int *i)
{
	char	*value;
	char	*new;
	int		value_len;

	while (i[2] != -1)
	{
		i[1] = i[2];
		i[2]++;
		while (raw_cmd[i[0]][i[2]] && !is_expkey_end(raw_cmd[i[0]][i[2]]))
			i[2]++;
		value = get_expand(raw_cmd[i[0]] + i[1], i[2] - i[1], data);
		new = make_expand(raw_cmd[i[0]], value, i[2] - i[1]);
		if (!new)
			return (0);
		raw_cmd[i[0]] = new;
		if (!value)
			value_len = 0;
		else
			value_len = ft_strlen(value);
		i[2] = is_exp(raw_cmd[i[0]] + (i[1] + value_len));
		free(value);
	}
	return (1);
}

/*
i[0][0] = i
//i[0][1] = tmp
i[0][2] = exp_i 
*/
int	pars_exp(t_data *data, char **raw_cmd)
{
	int		i[3];

	i[0] = 0;
	if (!raw_cmd)
		return (1);
	while (raw_cmd[i[0]])
	{
		i[2] = is_exp(raw_cmd[i[0]]);
		if (!pars_exp_loop(data, raw_cmd, i))
			return (0);
		i[0]++;
	}
	return (1);
}
