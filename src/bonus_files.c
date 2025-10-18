/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/18 20:57:18 by marimoli         ###   ########.fr       */
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
	return fd;
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
