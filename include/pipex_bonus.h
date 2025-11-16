/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/16 16:28:14 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

/* ======= Here_doc management fd_hd_bonus.c ======= */
void	here_doc(char **av);
int		open_heredoc_fd(char *limiter);
int		open_input_fd(char **argv, int heredoc);
int		open_output_fd(char *outfile, int heredoc);

/* ======= Input parsing get_bonus.c ======= */
int		get_next_line(char **line);
int		get_cmd_count(int argc, int heredoc);

/* ======= Execution pipex_bonus.c ======= */
void	exec(char *cmd, char **envp);
void	do_pipe(char *cmd, char **envp);
void	setup_fds(int ac, char **av, int *i, int *fd_out);

#endif
