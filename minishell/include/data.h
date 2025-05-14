/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/14 12:08:45 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_part
{
	char	*str;
	int		type;
}	t_part;

typedef struct	s_cmd
{
	t_part	*parts;
	char	*infile;
	char	*outfile;
}	t_cmd;