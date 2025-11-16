/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/16 19:30:42 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Ejecuta un comando simple redirigiendo stdin y stdout ====== */
void	exec(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		ft_error("malloc failed");
	path = get_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free(args);
		exit(127);
	}
	if (execve(path, args, envp) == -1)
		ft_error("execve failed");
	ft_free(args); 
}

/* ====== Ejecuta un comando dentro de pipe ====== */
void	do_pipe(char *cmd, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error("fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]); // cerrar el descriptor extra
		if (execve("/bin/sh", (char *[]){"sh", "-c", cmd, NULL}, envp) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		wait(NULL);
	}
}

/* ====== Gestiona apertura de archivos y here_doc ====== */
void	setup_fds(int ac, char **av, int *i, int *fd_out)
{
	int	fd_in;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 5)
		{
			ft_putendl_fd
			("Usa:./pipex_bonus here_doc LIMITER cmd1 cmd2 ... outfile", 2);
			exit(1);
		}
		*i = 2;  // Primer comando
    fd_in = open_input_fd(av, 0);
    *fd_out = open_output_fd(av[ac - 1], 0);
    dup2(fd_in, STDIN_FILENO);
	}
	else
	{
		if (ac < 5)
		{
			ft_putendl_fd("Usa:./pipex_bonus infile cmd1 cmd2 ... outfile", 2);
			exit(1);
		}
		*i = 2;  // Primer comando
		fd_in = open_input_fd(av, 0);
		*fd_out = open_output_fd(av[ac - 1], 1);
		dup2(fd_in, STDIN_FILENO);
	}
}

/* ====== Main  ====== */
int	main(int ac, char **av, char **envp)
{
	int	i;
	int	fd_out;

	setup_fds(ac, av, &i, &fd_out);
	while (i < ac - 2)
		do_pipe(av[i++], envp);  
	dup2(fd_out, STDOUT_FILENO);
	exec(av[ac - 2], envp); 
		return (0);
}

