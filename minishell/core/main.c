/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:53:42 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/16 15:51:19 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/data.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;
	
	(void)argc;
	(void)argv;
	(void)envp;
	data = malloc(sizeof(t_data));
	while (1)
	{
		input = readline("prompt.png>");
		if (input)
		{
			ft_printf("%s", input);
			if (ft_strlen(input) >= 1)
			{
				add_history(input);
				//pars(data, input);
				//exec(data);
				ft_printf("\n");
			}
			free(input);
		}
	}
	return (EXIT_FAILURE);
}
