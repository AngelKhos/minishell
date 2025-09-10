/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde <bde@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:38:22 by authomas          #+#    #+#             */
/*   Updated: 2025/02/11 15:37:06 by bde              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*count;

	count = ft_lstlast(*lst);
	if (count != NULL)
		count->next = new;
	else
		ft_lstadd_front(lst, new);
}
