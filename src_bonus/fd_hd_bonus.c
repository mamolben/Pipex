/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_hd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/07 19:26:27 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/** * @brief Implementa la funcionalidad de heredoc (lectura hasta limiter).  */
int	open_heredoc_fd(char *limiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		ft_error("pipe failed");
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		if (get_next_line(&line) <= 0
			|| !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

/**  * @brief Abre el archivo de entrada o el heredoc. */
int	open_input_fd(char **argv, int heredoc)
{
	if (heredoc)
		return (open_heredoc_fd(argv[2]));
	else
		return (open(argv[1], O_RDONLY));
}

/**  * @brief Abre el archivo de salida según modo (append o trunc).  */
int	open_output_fd(char *outfile, int heredoc)
{
	int	flags;

	flags = O_CREAT | O_WRONLY | (heredoc ? O_APPEND : O_TRUNC);
	return (open(outfile, flags, 0644));
}









