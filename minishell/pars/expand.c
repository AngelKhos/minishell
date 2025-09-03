/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:57:57 by authomas          #+#    #+#             */
/*   Updated: 2025/09/03 18:16:34 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char	*get_expand(char *key_src, int key_size, t_data *data)
{
	char	*key;
	t_env	*root;
	char	*name;

	key = ft_strndup(key_src + 1, key_size - 1);
	root = tree_search(data->env, key);
	free(key);
	if (!root)
		return (NULL);
	name = ft_strdup(root->data.value);
	if (!name)
		return (NULL);
	return (name);
}

int	is_exp(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			i = skip_quote(input, i);
		if (input[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

/* 
	cas a gerer:
	export me=h
	ec"$me"o -> renvois echo
	ec"$meo"o -> renvois eco
	ec$meo -> renvois ec
	echo $me -> ecris h
	echo $meo -> ecris rien
	echo '$me' -> ecris $me
	echo '$meo' -> ecris $meo
*/

char	*make_expand(char *token, char *value, int key_len)
{
	int		i;
	int		j;
	int		value_len;
	char	*new_token;

	i = 0;
	j = 0;
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	new_token = ft_calloc(sizeof(char), ft_strlen(token) + value_len);
	if (!new_token)
		return (NULL);
	while (token[i] && token[i] != '$')
		new_token[j++] = token[i++];
	if (value)
		ft_strlcat(new_token, value, ft_strlen(new_token) + value_len + 1);
	j += value_len;
	i += key_len;
	while (token[i])
		new_token[j++] = token[i++];
	return (new_token);
}

//i[0][0] = i
//i[0][1] = tmp
//i[0][2] = exp_i
int	pars_exp(t_data *data, char **raw_cmd)
{
	int		i[3];
	char	*value;
	char	*new;

	i[0] = 0;
	while (raw_cmd[i[0]])
	{
		i[2] = is_exp(raw_cmd[i[0]]);
		if (i[2] != -1)
		{
			i[1] = i[2];
			while (raw_cmd[i[0]][i[2]] && (!ft_isspace(raw_cmd[i[0]][i[2]]) && raw_cmd[i[0]][i[2]] != '"'))
				i[2]++;
			value = get_expand(raw_cmd[i[0]] + i[1], i[2] - i[1], data);
			new = make_expand(raw_cmd[i[0]], value, i[2] - i[1]);
			if (!new)
				return (0);
			free(value);
			free(raw_cmd[i[0]]);
			raw_cmd[i[0]] = new;
		}
		i[0]++;
	}
	return (1);
}
