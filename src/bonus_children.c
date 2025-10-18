/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 21:03:51 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/18 21:06:41 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

// Ejecuta una orden con búsqueda y split correctos
static void	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_error("malloc failed");
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		ft_error_cmd(cmd_args[0]);
	if (execve(cmd_path, cmd_args, envp) == -1)
		ft_error("execve failed");
}

// Primer hijo: entrada archivo, salida pipe
void	execute_first_child(char *cmd, char *envp[], int pipefd[2], int infile)
{
	if (dup2(infile, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
		ft_error("dup2 failed");
	close(pipefd[0]);
	close(infile);
	exec_cmd(cmd, envp);
}

// Hijos intermedios: entrada pipe previo, salida pipe siguiente
void	execute_middle_child(char *cmd, char *envp[], int pipefd_prev[2],
	int pipefd_next[2])
{
	if (dup2(pipefd_prev[0], STDIN_FILENO) < 0 || dup2(pipefd_next[1], STDOUT_FILENO) < 0)
		ft_error("dup2 failed");
	close(pipefd_prev[1]);
	close(pipefd_next[0]);
	exec_cmd(cmd, envp);
}

// Último hijo: entrada pipe previo, salida archivo
void	execute_last_child(char *cmd, char *envp[], int pipefd[2], int outfile)
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed");
	close(pipefd[1]);
	close(outfile);
	exec_cmd(cmd, envp);
}

// Espera a que terminen todos los hijos
void	wait_for_all(int child_count)
{
	int i;
	
	i = 0;
	while (i < child_count)
	{
		wait(NULL);
		i++;
	}
}
