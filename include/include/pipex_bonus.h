/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/20 20:20:26 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

// Prototipos de funciones modificadas

/* files */
int		open_file_in(char *filename, int argc);
int		open_file_out(char *filename, int argc);
int		open_file_out_append(char *filename, int argc);  // Si decides usarla
int		create_heredoc_file(char *limiter);

/* children */
void	execute_first_child(char **argv, char **envp, int *pipes, int infile, int is_heredoc);
void	execute_middle_child(char **argv, char **envp, int *pipes, int i, int is_heredoc);
void	execute_last_child(char **argv, char **envp, int *pipes, int outfile, int i, int is_heredoc);
void	wait_for_all(int child_count);

#endif
