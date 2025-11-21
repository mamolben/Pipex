/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_hd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/21 20:15:32 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Manejo del here_doc ====== */
void	here_doc(char **av) //+25
{
	int		p_fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(p_fd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			if (get_next_line(&line) <= 0)
				break;
			if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
			{
				free(line);
				exit(0);
			}
			ft_putstr_fd(line, p_fd[1]);
			ft_putstr_fd("\n", p_fd[1]);
			free(line);
		}
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

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

/* ====== Abre el archivo de entrada o el heredoc. ====== */
int	open_input_fd(char **argv, int heredoc)
{
	if (heredoc)
		return (open_heredoc_fd(argv[2]));
	else
		return (open(argv[1], O_RDONLY));
}

/* ====== Abre el archivo de salida según modo (append o trunc). ====== */
int	open_output_fd(char *outfile, int heredoc)
{
    int flags;

	if (heredoc)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	return (open(outfile, flags, 0644));
}
