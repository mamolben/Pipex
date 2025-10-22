/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:03:51 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/20 20:39:32 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		i;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		handle_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		handle_error("Command not found");
	if (execve(cmd_path, cmd_args, envp) == -1)
		handle_error("execve failed");
	// Liberar memoria si lo quieres aquí (cmd_args, cmd_path), depende de ft_split y get_cmd_path
}

void	execute_first_child(char **argv, char **envp, int *pipefd, int infile, int is_heredoc)
{
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(argv[2 + is_heredoc], envp);
}

void	execute_middle_child(char **argv, char **envp, int *prev_pipe, int *next_pipe, int i, int is_heredoc)
{
	dup2(prev_pipe[0], STDIN_FILENO);
	dup2(next_pipe[1], STDOUT_FILENO);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	close(next_pipe[0]);
	close(next_pipe[1]);
	exec_cmd(argv[i + 2 + is_heredoc], envp);
}

void	execute_last_child(char **argv, char **envp, int *prev_pipe, int outfile, int i, int is_heredoc)
{
	dup2(prev_pipe[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	exec_cmd(argv[i + 2 + is_heredoc], envp);
}

int	create_heredoc_file(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_error("heredoc open failed");

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	return (fd);
}

