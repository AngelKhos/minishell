/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:41:26 by authomas          #+#    #+#             */
/*   Updated: 2025/08/27 12:15:40 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"

typedef struct s_pair t_pair;

struct s_pair
{
	char *key;
	char *value;
};

typedef struct s_env
{
	t_pair data;
	struct s_env *left;
	struct s_env *right;
} t_env;

char	**tree_to_envp(t_env *root);

t_env	*env_parse_node(char *envstr);
int		env_parse_str(char *envstr, t_pair *out);
t_env	*envp_to_tree(char **envp);

void	destroy_data(t_pair *data);
void	tree_remove(t_env **root, char *key);

t_env	*tree_insert(t_env *node, t_env *leaf);

t_env	*tree_search(t_env *root, char *key);

void	tree_destroy(t_env *root);
void	tree_delete_node(t_env *node);

void	print_tree(t_env *root, int ex);

#endif
