/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:01:28 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/16 16:30:04 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ====== proceso hijo ======= */
void	process_child(char *argv[], char *envp[], int pipefd[], int infile)
{
	char	**cmd_args;
	char	*cmd_path;

	if (dup2(infile, STDIN_FILENO) < 0)
		ft_error("dup2 failed (child - infile to stdin)");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_error("dup2 failed (child - pipefd to stdout)");
	close(pipefd[0]);
	close(infile);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
	{
		ft_error("Error: ft_split failed in child process");
		exit(EXIT_FAILURE);
	}
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_error_cmd(cmd_args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, cmd_args, envp) == -1) 
	{
 		perror("execve failed (child)");
		exit(EXIT_FAILURE);
	}
}

/* ====== proceso padre ======= */
void	process_parent(char *argv[], char *envp[], int pipefd[], int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		ft_error("dup2 failed (parent - pipefd to stdin)");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed (parent - outfile to stdout)");
	close(pipefd[1]);
	close(outfile);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		ft_error("ft_split failed in parent process");
	cmd_path = get_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
 		perror("execve failed");
		exit(EXIT_FAILURE);
	}
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
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);	
	waitpid(pid1, NULL, 0);	
	waitpid(pid2, NULL, 0);	
}

/* ====== Ejecución de dos comandos. ====== */
int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outfile;

	ft_error_argc(argc);	
	init_fds(argv, &infile, &outfile);	
	execute(argv, envp, infile, outfile);	
	return (0);
}

