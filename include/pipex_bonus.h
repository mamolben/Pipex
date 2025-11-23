/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 16:22:36 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

/* ========= PIPE PROCESSING (pipe_process_bonus.c) ========= */
void	do_pipe(char *cmd, char **envp);
int		open_heredoc_fd(char *limiter);
int		get_next_line(char **line);

/* ========= FD SETUP COMMAND EXECUTION (pipex_bonus.c) ========= */
void	setup_fds(int ac, char **av, int *i, int *fd_out);
void	exec_cmd(char *cmd, char **envp);

#endif
