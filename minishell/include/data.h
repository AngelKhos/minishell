/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/07/24 15:04:10 by gchauvet         ###   ########.fr       */
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
	t_cmd	*cmd; // the command to update in the parsing at each call of readline
	int		run;
	int		nb_pipes;
	int		exit_code;
}	t_data;

extern int	g_pid;

////////////// BUILTINS //////////////

int		pwd(t_data *data);
int		cd(t_data *data, t_cmd cmd);
void	exit_minishell_edition(t_data *dat, char *ms);
int		ft_export(t_data *data, char *arg);
int		env(t_data *data);
int		echo(t_cmd cmd);

//////////////// FREE ////////////////

void	free_array(char **array);
void	free_data(t_data *data);
void	free_cmd(t_data *data);

//////////////// INIT ////////////////

void	init_data(t_data *data, char **envp);

//////////////// EXEC ////////////////

void	exec_builtins(t_data *data, int prevpipe[2], int *pids, int cmd_index);
void    builtins_if(t_data *data, int cmd_index);
int     is_exit_or_cd(t_data *data, int cmd_index);
void	read_cmd_end_close(t_data *data, int prev_pipe[2]);
void	close_child_pipe(int prev_pipe[2], int curr_pipe[2]);
void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
void	read_cmd_if(t_data *data, int cmd_index, int prev_pipes[2], int *pids);
void	exec_cmd(t_data *data, int prev_pipe[2], int *pids, int cmd_index);
int		execute(char *cmd_arg, char **envp);
void	wait_all(t_data *data, int *pids);
void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
char	*convert_part_to_arg(t_data *data, int index);
void	redir_file(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
void	child_porc(t_data *data, int prev_pipe[2], int curr_pipe[2], int cmd_index);
void	read_cmd(t_data *data);
int		here_doc(t_data *data, char *word);
void	close_redir(t_data *data);

//////////////// DEBUG ///////////////

void	print_char_array(char **array);
void	display_cmd(t_data *data);

/////////////// PARSING /////////////

char	**ms_split(char *input_str, char separator);
int		parsing(t_data *data);

/////////////// SIGNALE /////////////

void	handle_signal();
void	sigint_handle();
void	sigabrt_handle();

/////////////// RANDOM //////////////

char	*get_prompt(t_data *data);

#endif