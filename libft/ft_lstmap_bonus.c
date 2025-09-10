/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:30:41 by authomas          #+#    #+#             */
/*   Updated: 2024/11/28 15:58:46 by authomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Arguments de lst_map:
 * lst -> liste source
 * function f -> fais des sur liste, et retourne un nouveau content
 * function del -> 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*nbuff;

	nbuff = malloc(sizeof(t_list));
	if (!lst || !nbuff)
		return (free(nbuff), NULL);
	nbuff->next = NULL;
	nbuff->content = f(lst->content);
	lst = lst->next;
	while (lst != NULL)
	{
		new_lst = malloc(sizeof(t_list));
		if (!new_lst)
		{
			ft_lstclear(&nbuff, del);
			return (NULL);
		}
		new_lst->next = NULL;
		new_lst->content = f(lst->content);
		ft_lstadd_back(&nbuff, new_lst);
		lst = lst->next;
	}
	new_lst = nbuff;
	return (new_lst);
}
