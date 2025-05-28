/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/05/28 14:01:16 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	char	*input;
	t_ast	*env;
	char	**envp; // temp
	t_cmd	*cmd; // the command to update in the parsing at each call of readline
}	t_data;

////////////// BUILTINS //////////////

void	pwd(t_data *data);
void	cd(t_data *data, char *cd_args);
void	exit_minishell_edition(t_data *data);

//////////////// FREE ////////////////

void	free_array(char **array);
void	free_data(t_data *data);

//////////////// INIT ////////////////

void	init_data(t_data *data, char **envp);

//////////////// EXEC ////////////////

int	execute(char *cmd_arg, char **envp);
void	read_cmd(t_data *data, t_cmd *cmd);