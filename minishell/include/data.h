/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/24 15:06:28 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define CMD 1 // cat echo ls pwd...
# define ARG 2 // -l "hello world"...
# define PIPE 3 // |
# define OUTFILE 4 // >
# define INFILE 5 // <
# define HEREDOC 6 // <<
# define APPEND 7 // >>
# define ENVVAR 8 // $variable_name

typedef struct	s_part
{
	char	*str;
	int		type;
}	t_part;

typedef struct	s_cmd
{
	t_part	*parts;
	int		len;
	char	*infile;
	char	*outfile;
}	t_cmd;

typedef struct s_data
{
	char	*curent_path;
	t_cmd	*cmd; // the command to update in the parsing at each call of readline
}	t_data;

////////////// BUILTINS //////////////

void	pwd(t_data *data);
void	cd(t_data *data, char *cd_args);

//////////////// FREE ////////////////

void free_data(t_data *data);

//////////////// INIT ////////////////

void	init_data(t_data *data);