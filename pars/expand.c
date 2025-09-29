/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:57:57 by authomas          #+#    #+#             */
/*   Updated: 2025/09/29 14:55:31 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char	*get_expand(char *key_src, int key_size, t_data *data)
{
	char	*key;
	t_env	*root;
	char	*value;

	if (key_src[1] == '?')
	{
		value = ft_itoa(data->exit_code);
		if (!value)
			return (NULL);
		return (value);
	}
	key = ft_strndup(key_src + 1, key_size - 1);
	if (!key)
		return (NULL);
	root = tree_search(data->env, key);
	free(key);
	if (!root)
		return (NULL);
	value = ft_strdup(root->data.value);
	if (!value)
		return (NULL);
	return (value);
}

char	*make_expand(char *t, char *value, int keylen)
{
	char	*n_token;
	int		i[2];
	int		value_len;

	i[0] = 0;
	i[1] = 0;
	value_len = keylen;
	if (value)
		value_len = ft_strlen(value);
	n_token = ft_calloc(sizeof(char), ft_strlen(t) + value_len);
	if (!n_token)
		return (NULL);
	while (t[i[0]] && t[i[0]] != '$')
		n_token[i[1]++] = t[i[0]++];
	if (!value)
		ft_strlcpy(n_token + i[1], t + i[0] + keylen, ft_strlen(t) - i[0] + 1);
	else
	{
		ft_strlcat(n_token, value, ft_strlen(n_token) + value_len + 1);
		i[1] += value_len;
		i[0] += keylen;
		ft_strlcpy(n_token + i[1], t + i[0], ft_strlen(t) - i[0] + 1);
	}
	free(t);
	return (n_token);
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
		while ((*raw_cmd)[i[2]] && !is_expkey_end((*raw_cmd)[i[2]]))
		{
			i[2]++;
		}
		value = get_expand(*raw_cmd + i[1], i[2] - i[1], data);
		new = make_expand(*raw_cmd, value, i[2] - i[1]);
		if (!new)
		{
			free(value);
			return (0);
		}
		*raw_cmd = new;
		if (!value)
			value_len = 0;
		else
			value_len = ft_strlen(value);
		i[2] = is_exp(*raw_cmd + (i[1] + value_len));
		if (i[2] != -1)
			i[2] += i[1] + value_len;
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

	(void)i[0];
	if (!raw_cmd)
		return (1);
	i[2] = is_exp(*raw_cmd);
	if (!pars_exp_loop(data, raw_cmd, i))
		return (0);
	return (1);
}
