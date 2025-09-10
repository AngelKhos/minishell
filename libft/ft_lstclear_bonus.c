/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde <bde@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:21:40 by authomas          #+#    #+#             */
/*   Updated: 2025/02/11 15:36:43 by bde              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*count;
	t_list	*temp;

	count = *lst;
	while (count != NULL)
	{
		del(count->content);
		temp = count->next;
		free(count);
		count = NULL;
		count = temp;
	}
	*lst = NULL;
}
