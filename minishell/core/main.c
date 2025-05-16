/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/14 16:01:03 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	char	*input;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("prompte.png>");
		if (input)
		{
			add_history(input);
			ft_printf("%s", input);
			if (ft_strlen(input) >= 1)
				ft_printf("\n");
			free(input);
		}
	}
	return (EXIT_FAILURE);
}