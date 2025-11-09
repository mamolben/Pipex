/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:26:26 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/09 17:49:53 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Manejo genenal de errores del sistema */
void	ft_error(const char *msg)
{
	write(2, "Error: ", 7);
	perror(msg);
	exit(EXIT_FAILURE);
}

/* Comando no encontrado */
void	ft_error_cmd(const char *cmd)
{
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
	}
	write(2, ": command not found\n", 20);
	exit(127);
}

/* Archivo no encontrado */
void	ft_error_file(const char *file)
{
	if (file)
	{
		write(2, file, ft_strlen(file));
	}
	write(2, ": No such file or directory\n", 28);
	exit(1);
}

/* Verifica cantidad correcta de argumentos  y muestra el formato de uso */
void	ft_error_argc(int argc)
{
	if (argc != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		exit(EXIT_FAILURE);
	}
}
