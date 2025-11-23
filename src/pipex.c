/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:01:28 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 13:25:45 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ======Ejecuta el primer comando: cmd1 < infile ======*/
void	process_child(char *argv[], char *envp[], int pipefd[], int infile)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		ft_error("ft_split failed (child)");
	if (dup2(infile, STDIN_FILENO) < 0)
		ft_error("dup2 infile failed (child)");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_error("dup2 pipefd[1] failed (child)");
	close(pipefd[0]);
	close(infile);
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	execve(cmd_path, cmd_args, envp);
	perror("execve failed (child)");
	exit(EXIT_FAILURE);
}

/* =======Ejecuta el segundo comando: pipe -> cmd2 > outfile ======*/
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile)
{
	char **cmd_args;
	char *cmd_path;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		ft_error("dup2 pipefd[0] failed (parent)");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 outfile failed (parent)");
	close(pipefd[1]);
	close(outfile);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		ft_error("ft_split failed (parent)");
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	execve(cmd_path, cmd_args, envp);
	perror("execve failed (parent)");
	exit(EXIT_FAILURE);
}

/* ====== Inicializa archivos ======= */
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

/* ====== Ejecución del pipe ====== */
void	execute(char *argv[], char *envp[], int infile, int outfile)
{
	int	pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) < 0)
		ft_error("pipe failed");
	pid1 = fork();
	if (pid1 < 0)
		ft_error("fork failed (pid1)");
	if (pid1 == 0)
	process_child(argv, envp, pipefd, infile);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("fork failed (pid2)");
	if (pid2 == 0)
		process_parent(argv, envp, pipefd, outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/* ====== main ====== */
int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outfile;

	ft_error_argc(argc);
	init_fds(argv, &infile, &outfile);
	execute(argv, envp, infile, outfile);
	return (0);
}
