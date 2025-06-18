/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:34:36 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/18 16:47:28 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data.h"
#include "../libft/libft.h"
#include <readline/readline.h>

void	here_doc(t_data *data, char *word)
{
	(void)data;
	char	*here_doc_input;
	here_doc_input = readline(">");
	while (ft_strncmp(here_doc_input, word, -1) != 0)
	{
		here_doc_input = readline(">");
	}
}