/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:41:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/18 21:08:41 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*files*/
int	open_file_in(char *filename, int argc);
int	open_file_out(char *filename, int argc);

/*children*/
void	execute_first_child(char *cmd, char *envp[], int pipefd[2], int infile);
void	execute_middle_child(char *cmd, char *envp[], int pipefd_prev[2], 
	int pipefd_next[2]);
void	execute_last_child(char *cmd, char *envp[], int pipefd[2], int outfile);
void	wait_for_all(int child_count);

#endif