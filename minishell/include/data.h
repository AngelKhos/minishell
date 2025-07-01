/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/06/30 13:20:23 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "env.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <linux/limits.h>
#include <readline/chardefs.h>
#include <limits.h>


enum cmd_type {
	CMD = 1, // cat echo ls pwd...
	ARG, // -l "hello world"...
	BUIL, // builtins
};

typedef struct	s_part
{
	char			*str;
	enum cmd_type	type;
}	t_part;

typedef struct	s_cmd
{
	t_part	*parts;
	int		len;
	int		infile;
	int		outfile;
	int		here_doc;
}	t_cmd;

typedef struct s_data
{
	char	*curent_path;
	char	*input;
	t_env	*env;
	char	**envp; // temp
	t_cmd	*cmd; // the command to update in the parsing at each call of readline
	int		nb_pipes;
}	t_data;

////////////// BUILTINS //////////////

void	pwd(t_data *data);
void	cd(t_data *data, char *cd_args);
void	exit_minishell_edition(t_data *data);
void	env(t_data *data);
void	echo(t_cmd cmd);

//////////////// FREE ////////////////

void	free_array(char **array);
void	free_data(t_data *data);
void	free_cmd(t_data *data);

//////////////// INIT ////////////////

void	init_data(t_data *data, char **envp);

//////////////// EXEC ////////////////

void	exec_builtins(t_data *data, int prevpipe[2], int *pids, int cmd_index);
void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
int		execute(char *cmd_arg, char **envp);
void	read_cmd(t_data *data);
int		here_doc(t_data *data, char *word);
void	close_redir(t_data *data);

//////////////// DEBUG ///////////////

void	display_cmd(t_data *data);
int first_check(char *input);
int	parsing(t_data *data);

/////////////// SIGNALE /////////////

void	handle_signal();
void	sigint_handle();
void	sigabrt_handle();

#endif