/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/19 18:08:17 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	int		cmd_count;
	int		**pipes;
	int		is_heredoc;
}	t_pipex;

/* files */
int		open_file_in(char *filename);
int		open_file_out(char *filename);
int		open_file_out_append(char *filename);
int		create_heredoc_file(char *limiter);

/* children */
void	execute_first_child(t_pipex *px, int i);
void	execute_middle_child(t_pipex *px, int i);
void	execute_last_child(t_pipex *px, int i);
void	wait_for_all(int child_count);

#endif

/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*files*/
int		open_file_in(char *filename, int argc);
int		open_file_out(char *filename, int argc);

/*children*/
void	execute_first_child(char *cmd, char *envp[], int pipefd[2], int infile);
void	execute_middle_child(char *cmd, char *envp[], int pipefd_prev[2],
			int pipefd_next[2]);
void	execute_last_child(char *cmd, char *envp[], int pipefd[2], int outfile);
void	wait_for_all(int child_count);

#endif
