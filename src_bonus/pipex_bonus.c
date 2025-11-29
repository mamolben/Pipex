/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 19:51:18 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Abre infile o here_doc y asigna fd_out ====== */
void	setup_fds(int ac, char **av, int *i, int *fd_out)
{
	int	fd_in;
	int	heredoc;

	heredoc = !ft_strncmp(av[1], "here_doc", 8);

	if (ac < 5 + heredoc)
	{
		ft_putendl_fd("Uso incorrecto", 2);
		exit(1);
	}
	if (heredoc)
	{
		*i = 3;
		fd_in = open_heredoc_fd(av[2]);
		*fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		*i = 2;
		fd_in = open(av[1], O_RDONLY);
		*fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

/* ====== Ejecuta el último comando ====== */
void	exec_cmd(char *cmd, char **envp)
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
	execve(path, args, envp);
	ft_error("execve failed");
}

/* ====== main ====== */
int	main(int ac, char **av, char **envp)
{
	int	i;
	int	fd_out;

	setup_fds(ac, av, &i, &fd_out);
	while (i < ac - 2)
		do_pipe(av[i++], envp);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	exec_cmd(av[ac - 2], envp);
}
