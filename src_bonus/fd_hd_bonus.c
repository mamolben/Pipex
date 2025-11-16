/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_hd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:54:59 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/16 19:33:59 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Manejo del here_doc ====== */
void	here_doc(char **av)
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
		close(p_fd[0]); // cerrar lectura
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
			ft_putstr_fd("\n", p_fd[1]); // agregar salto de línea
			free(line);
		}
	}
	else
	{
		close(p_fd[1]);         // cerrar escritura
		dup2(p_fd[0], STDIN_FILENO); // redirigir stdin
		wait(NULL);             // esperar al hijo
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
int		open_input_fd(char **argv, int heredoc)
{
	if (heredoc)
		return (open_heredoc_fd(argv[2]));
	else
		return (open(argv[1], O_RDONLY));
}

/* ====== Abre el archivo de salida según modo (append o trunc). ====== */
int open_output_fd(char *outfile, int heredoc)
{
    int flags;

    if (heredoc)
        flags = O_CREAT | O_WRONLY | O_APPEND;
    else
        flags = O_CREAT | O_WRONLY | O_TRUNC;

    return (open(outfile, flags, 0644));
}


/*   intento de simplificar  

void close_pipe_ends(int *p_fd)
{
    close(p_fd[0]);
    close(p_fd[1]);
}

void handle_child_process(int *p_fd, char *delimiter)
{
    char *line;

    close(p_fd[0]);  // Cerrar lectura en el hijo

    while (1)
    {
        if (get_next_line(&line) <= 0)
            break;

        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            exit(0);  // Terminar el hijo si encuentra el delimitador
        }

        ft_putstr_fd(line, p_fd[1]);
        ft_putstr_fd("\n", p_fd[1]);  // Agregar salto de línea
        free(line);
    }
}

void handle_parent_process(int *p_fd)
{
    close(p_fd[1]);             // Cerrar escritura en el padre
    dup2(p_fd[0], STDIN_FILENO);  // Redirigir la entrada estándar al pipe
    wait(NULL);                  // Esperar al proceso hijo
}

void here_doc(char **av)
{
    int p_fd[2];
    pid_t pid;

    if (pipe(p_fd) == -1)
        ft_error("pipe failed");
    pid = fork();
    if (pid == -1)
        ft_error("fork failed");
    if (pid == 0)
        handle_child_process(p_fd, av[2]);  // Hijo maneja la entrada
    else
        handle_parent_process(p_fd);  // Padre maneja el redireccionamiento
}
close_pipe_ends: cierra ambos extremos del pipe

handle_child_process: maneja el comportamiento del proceso hijo. 
Lee líneas del estándar de entrada (usando get_next_line), y si encuentra una 
línea que coincida con el delimitador proporcionado (av[2]), termina el proceso
hijo. Si no, escribe la línea en el pipe.

handle_parent_process: El proceso padre cierra el extremo de escritura del pipe, 
redirige la entrada estándar (stdin) hacia el extremo de lectura del pipe
usando dup2, y luego espera a que el hijo termine con wait(NULL).

here_doc: maneja el fork, la creación del pipe y la delegación de responsabilidades 
entre el proceso padre e hijo. Se encarga de iniciar el pipe, hacer el fork 
y luego delegar el comportamiento a las funciones auxiliares.
*/
