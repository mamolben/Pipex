/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/20 20:42:46 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	open_file_in(char *filename, int argc)
{
	int	fd;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus [here_doc LIMITER] cmd1 ... cmdN outfile\n", 63);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(filename);
	return (fd);
}

int	open_file_out(char *filename, int append, int argc)
{
	int	fd;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus [here_doc LIMITER] cmd1 ... cmdN outfile\n", 63);
		exit(EXIT_FAILURE);
	}
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_error(filename);
	return (fd);
}

int	**init_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		handle_error("malloc failed");
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			handle_error("malloc failed");
		if (pipe(pipes[i]) == -1)
			handle_error("pipe failed");
		i++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}


