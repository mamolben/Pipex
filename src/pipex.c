/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:01:28 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/09 19:28:06 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* ====== proceso hijo ======= */
void	process_child(char *argv[], char *envp[], int pipefd[], int infile)
{
	char	**cmd_args;
	char	*cmd_path;

	if (dup2(infile, STDIN_FILENO) < 0)
		ft_error("dup2 failed");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_error("dup2 failed");
	close(pipefd[0]);
	close(infile);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		ft_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	execve(cmd_path, cmd_args, envp);
	ft_error("execve failed");
}

/* ====== proceso padre ======= */
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		ft_error("dup2 failed");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed");
	close(pipefd[1]);
	close(outfile);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		ft_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	execve(cmd_path, cmd_args, envp);
	ft_error("execve failed");
}

/* ====== inicializa los descriptores de archivo ======= */
void	init_fds(char *argv[], int *infile, int *outfile)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
		ft_error_file(argv[1]);
	*outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		close(*infile);
		ft_error_file(argv[4]);
	}
}

/* ====== Ejecución de la lógica de pipex. ====== */
void	execute(char *argv[], char *envp[], int infile, int outfile)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) < 0)
		ft_error("Pipe creation failed");
	pid1 = fork();
	if (pid1 < 0)
		ft_error("Fork failed");
	if (pid1 == 0)
		process_child(argv, envp, pipefd, infile);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Fork failed");
	if (pid2 == 0)
		process_parent(argv, envp, pipefd, outfile);
	//printf ("despues de comprobar error tubo, en execute \n");
	close(pipefd[0]);
	//printf ("despues de cerrar primer hijo \n");
	close(pipefd[1]);
	//printf ("despues de cerrar segundo hijo \n");
	close(infile);
	//printf ("despues de cerrar archivo de entrada \n");
	close(outfile);
	//printf ("despues de cerrar archivo de salida \n");
	waitpid(pid1, NULL, 0);
	//printf ("despues de esperar  cerrar pid1 \n");
	waitpid(pid2, NULL, 0);
	//printf ("despues de esperar  cerrar pid2 \n");
}

/* ====== Ejecución de dos comandos. ====== */
int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outfile;

	ft_error_argc(argc);
	//printf ("despues de error argumento \n");
	init_fds(argv, &infile, &outfile);
	//printf ("despues de iniciar descriptores \n");
	execute(argv, envp, infile, outfile);
	//printf ("despues de la ejecucion \n");
	return (0);
}

