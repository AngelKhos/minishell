/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:54:15 by ********          #+#    #+#             */
/*   Updated: 2025/05/06 14:08:11 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	*find_path(char *cmd, char **envp);
void	exit_error(char *error);
int		execute(char *cmd_arg, char **envp);
void	freearray(char **array);

#endif