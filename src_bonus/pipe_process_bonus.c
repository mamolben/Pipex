/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 17:58:45 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Procesamiento para la tubería ======= */
// Hijo: ejecuta el comando y escribe en la tubería
void	child_process(char *cmd, int *pipefd, char **envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exec_cmd(cmd, envp);
}

// Padre: lee de la tubería y redirige a stdin
void	parent_process(int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

/* ====== Crea una tubería y gestiona el proceso hijo/padre ====== */
void	do_pipe(char *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid < 0)
		ft_error("fork failed");
	if (pid == 0)
		child_process(cmd, pipefd, envp);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(pipefd);
	}
}

/* ====== Abre el heredoc y devuelve el fd de lectura. ====== */
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

/* ====== Lee una línea desde stdin hasta '\n' ====== */
int	get_next_line(char **line) 
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (r);
}