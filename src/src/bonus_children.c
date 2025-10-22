/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:03:51 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/19 18:24:35 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

static void	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	if (execve(cmd_path, cmd_args, envp) == -1)
		ft_error("execve failed");
}

void	execute_first_child(t_pipex *px, int i)
{
	dup2(px->infile, STDIN_FILENO);
	dup2(px->pipes[i][1], STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_command(px->argv[i + 2 + px->is_heredoc], px->envp);
}

void	execute_middle_child(t_pipex *px, int i)
{
	dup2(px->pipes[i - 1][0], STDIN_FILENO);
	dup2(px->pipes[i][1], STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_command(px->argv[i + 2 + px->is_heredoc], px->envp);
}

void	execute_last_child(t_pipex *px, int i)
{
	dup2(px->pipes[i - 1][0], STDIN_FILENO);
	dup2(px->outfile, STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_command(px->argv[i + 2 + px->is_heredoc], px->envp);
}

int	create_heredoc_file(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("heredoc open failed");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	return (fd);
}

void	wait_for_all(int child_count)
{
	int	i;

	i = 0;
	while (i < child_count)
	{
		wait(NULL);
		i++;
	}
}



#include "pipex.h"
#include "pipex_bonus.h"

static void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	if (execve(cmd_path, cmd_args, envp) == -1)
		ft_error("execve failed");
}

void	execute_first_child(t_pipex *px, int i)
{
	dup2(px->infile, STDIN_FILENO);
	dup2(px->pipes[i][1], STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_cmd(px->argv[i + 2 + px->is_heredoc], px->envp);
}

void	execute_middle_child(t_pipex *px, int i)
{
	dup2(px->pipes[i - 1][0], STDIN_FILENO);
	dup2(px->pipes[i][1], STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_cmd(px->argv[i + 2 + px->is_heredoc], px->envp);
}

void	execute_last_child(t_pipex *px, int i)
{
	dup2(px->pipes[i - 1][0], STDIN_FILENO);
	dup2(px->outfile, STDOUT_FILENO);
	close_all_pipes(px->pipes, px->cmd_count);
	exec_cmd(px->argv[i + 2 + px->is_heredoc], px->envp);
}

void	wait_for_all(int child_count)
{
	int	i;

	i = 0;
	while (i < child_count)
	{
		wait(NULL);
		i++;
	}
}
