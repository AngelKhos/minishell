/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ******** <*******************.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:54:15 by ********          #+#    #+#             */
/*   Updated: 2025/01/27 16:20:35 by ********         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	*find_path(char *cmd, char **envp);
void	exit_error(char *error);
int		execute(char *cmd_arg, char **envp, int file);
void	freearray(char **array);

#endif