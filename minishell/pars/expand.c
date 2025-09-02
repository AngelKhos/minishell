/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:57:57 by authomas          #+#    #+#             */
/*   Updated: 2025/09/02 14:08:38 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"

char *expand(char *key_src, int key_size, t_data *data)
{
	char *key;
	t_env *root;
	char *name;

	key = ft_strndup(key_src + 1, key_size - 1);
	root = tree_search(data->env, key);
	free(key);
	if (!root)
		return NULL;
	name = ft_strdup(root->data.value);
	if (!name)
		return NULL;
	return (name);
}

// int is_exp(char *input)
// {
// 	int i;

// 	i = 0;
// 	while(input[i])
// 	{
// 		if (input[i] == '\'')
// 			i = skip_quote(input, i);
// 		if (input[i] == '$')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }
// int exp_var_len(t_data *data, char *input)
// {
// 	int i;
// 	int tmp;
// 	int len;
// 	char *var;
// 	char *var_key;

// 	i = 0;
// 	len = 0;
// 	while(input[i])
// 	{
// 		if(input[i] == '$')
// 		{
// 			tmp = i;
// 			while(input[i] && input[i] != ' ')
// 				i++;
// 			var_key = ft_strndup(input + tmp, i - tmp);
// 			var = tree_search(data->env, var_key)->data.value;
// 			if (var)
// 				len += ft_strlen(var);
// 			free(var_key);
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// char *exp_var(t_data *data, char* input)
// {
// 	int i;
// 	char *new;

// 	i = 0;
// 	// while (input[i])
// 	// {
// 	// 	if ()
// 	// }
// 	return (new);
// }

// void pars_exp(t_data *data, char** inputs)
// {
// 	/* prenne mes string
// 		j'insere mes $var
// 		si $var est contenu dans '', j'ignore

// 		systeme de mode avec les quotes qui font differentes choses
// 		changement de toute la fonction, expand fait apres le split des commandes par ' '
// 		quand on trouve un dollar il faut regarder tout les characteres qui se trouvent apres jusqu'a un espace ou un eol
// 		si dans "", prendre $ jusqu'a la fin de quote ou espace
// 		cas a gerer:
// 		export me=h
// 		ec"$me"o -> renvois echo
// 		ec"$meo"o -> renvois eco
// 		ec$meo -> renvois ec
// 		echo $me -> ecris h
// 		echo $meo -> ecris rien
// 		echo '$me' -> ecris $me
// 		echo '$meo' -> ecris $meo
		
// 	*/
// 	int i;
// 	int exp_i;

// 	i = 0;
// 	while(inputs[i])
// 	{
// 		exp_i = is_exp(inputs[i]);
// 		if (!exp_i)
// 			i++;
// 		// else 
// 		// {
// 		// 	exp
// 		// }
// 	}
// }
// // 