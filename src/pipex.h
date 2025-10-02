/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:02:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/02 16:02:42 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

void   execute_cmd(char *argv, char **envp);
char *get_path(char *cmd, char **envp);
char **ft_split(char const *s, char c);
void   free_matrix(char **matrix);
void   exit_error(char *msg);
#endif
