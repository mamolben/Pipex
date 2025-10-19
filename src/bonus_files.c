/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/19 17:47:53 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_in(char *filename, int argc)
{
	int	fd;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error_file(filename);
	return (fd);
}

int	open_file_out(char *filename, int argc)
{
	int	fd;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_error_file(filename);
	return (fd);
}



#include "pipex.h"
#include "pipex_bonus.h"

int	open_file_in(char *filename)
{
	int	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error_file(filename);
	return (fd);
}

int	open_file_out(char *filename)
{
	int	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_error_file(filename);
	return (fd);
}

int	open_file_out_append(char *filename)
{
	int	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		ft_error_file(filename);
	return (fd);
}

int	create_heredoc_file(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("heredoc: cannot open temp file");

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
