/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:41:26 by authomas          #+#    #+#             */
/*   Updated: 2025/05/22 15:18:13 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct s_ast
{
	char *key;
	char *value;
	struct s_ast *left;
	struct s_ast *right;
	/* Potentially add *parent, maybe, idk */
} t_ast;

t_ast *leaf_from_env(char *envstr);
t_ast *tree_insert(t_ast *node, t_ast *leaf);
t_ast *tree_search(t_ast *root, char *key);
void tree_destroy(t_ast *root);
t_ast *envp_to_tree(char **envp);

#endif