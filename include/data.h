/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:16:25 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/28 19:42:43 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "env.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <readline/chardefs.h>
# include <limits.h>
# include <signal.h>

# define PIPE_LIMIT 512

enum e_cmd_type
{
	CMD = 1, // cat echo ls pwd...
	ARG, // -l "hello world"...
	BUIL, // builtins
};

typedef struct s_part
{
	char			*str;
	enum e_cmd_type	type;
}	t_part;

typedef struct s_cmd
{
	t_part	*parts;
	int		len;
	int		infile;
	int		outfile;
	int		here_doc;
	char	*hd_name;
}	t_cmd;

typedef struct s_data
{
	char	*curent_path;
	char	*input;
	t_env	*env;
	t_cmd	*cmd;
	int		run;
	int		nb_pipes;
	int		pid;
	int		exit_code;
}	t_data;

typedef struct s_redir
{
	char	*new_input;
	size_t	i;
	size_t	j;
	size_t	tmp;
}	t_redir;

extern int	g_sig_val;

////////////// BUILTINS //////////////

int		pwd(t_data *data);
int		cd(t_data *data, t_cmd cmd);
int		exit_minishell_edition(t_data *data, t_cmd *cmd);
int		ft_export(t_data *data, t_cmd *cmd);
int		env(t_data *data, int cmd_index);
int		echo(t_cmd cmd);
int		unset(t_data *data, int cmd_index);

//////////////// FREE ////////////////

void	free_array(char **array);
void	free_data(t_data *data);
void	free_cmd(t_data *data);
void	close_file(t_data *data);
void	close_here_doc(t_cmd *cmd);
void	double_free(void *ptr1, void *ptr2);

//////////////// INIT ////////////////

int		init_default_env(t_data *data);
int		init_data(t_data *data, char **envp);

//////////////// EXEC ////////////////

int		exec_builtins(t_data *data, int prevpipe[2], int *pids, int cmd_index);
int		builtins_if(t_data *data, int cmd_index);
int		is_exit_or_cd(t_data *data, int cmd_index);
void	read_cmd_end_close(t_data *data, int prev_pipe[2]);
void	close_child_pipe(int prev_pipe[2], int curr_pipe[2]);
void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
int		read_cmd_if(t_data *data, int cmd_index, int prev_pipes[2], int *pids);
int		exec_cmd(t_data *data, int prev_pipe[2], int *pids, int cmd_index);
int		execute(char **cmd, char **envp);
void	wait_all(t_data *data, int *pids);
void	redir_pipe(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
char	**convert_part_to_arg(t_data *data, int index);
void	redir_file(t_data *data, int pr_pip[2], int cur_pip[2], int cmd_index);
int		child_proc(t_data *data, int prev_pipe[2],
			int curr_pipe[2], int cmd_index);
int		read_cmd(t_data *data);
void	close_pipe_in_exec_cmd(int prev_pipe[2], int curr_pipe[2]);
void	close_redir(t_data *data);
void	close_redir_one_cmd(t_cmd cmd);

//////////////// DEBUG ///////////////

void	print_char_array(char **array);
void	display_cmd(t_data *data);

/////////////// PARSING /////////////

char	**ms_split(char *input_str, char *separator);
char	*strdup_wquotes(char *s);
char	*pars_redir(char *input, t_cmd *cmd, t_data *data);
int		skip_quote(char *str, int index);
char	*ft_strndup(const char *s, size_t n);
int		parsing(t_data *data);
int		is_builtins(char *input);
int		here_doc(char *word, char **hd_name, t_data *data);
int		pars_exp(t_data *data, char **raw_cmd);
char	*get_expand(char *key_src, int key_size, t_data *data);
int		is_expkey_end(char c);
int		get_tablen(char **inputs);
int		is_redir(char *input);
void	init_redir_fd(t_data *data, int input_len);
int		is_in_out(char c);
char	*get_name(char *input, int i, int j, t_data *data, int is_heredoc);
int		permission_denied(int type, char *name, t_data *data);
int		unexpected_token(int type, t_data *data);
int		is_exp(char *input);
int		checking_missing_command(char *input);
int		is_code(char *token, char **value, int *key_len, t_data *data);
int		handle_heredoc(char *input, t_cmd *cmd, t_data *data);
int		handle_infile(char *input, t_cmd *cmd, t_data *data);
int		handle_outfile(char *input, t_cmd *cmd, t_data *data);
char	*pars_redir(char *input, t_cmd *cmd, t_data *data);

/////////////// SIGNALS /////////////

void	handle_signal(void);
void	sigint_handle(int code);
void	sigabrt_handle(void);
void	exec_sigint_handle(int code);
void	hd_sigint_handle(int code);
int		rl_hook_event_handler(void);

#endif