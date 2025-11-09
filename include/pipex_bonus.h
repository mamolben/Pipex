/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/09 20:32:52 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

/* ======= Funciones de get_bonus.c ======= */
int		get_next_line(char **line);
int		get_cmd_count(int argc, int heredoc);

/* ======= Funciones de fd_hd_bonus.c ======= */
int		open_heredoc_fd(char *limiter);
int		open_input_fd(char **argv, int heredoc);
int		open_output_fd(char *outfile, int heredoc);

/* ======= Funciones de pipex_bonus.c ======= */
void	command(char *cmd, char **envp, int fd_in, int fd_out);
void	exec(char *cmd, char **env);
void	do_pipe(char *cmd, char **env);
void	here_doc(char **av);

/* ======= Helpers ======= */
char	*get_cmd_path(char *cmd, char **env);  // reemplaza get_path
void	ft_free(char **tab);                     // reemplaza ft_free_tab

#endif
