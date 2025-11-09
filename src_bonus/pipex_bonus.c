/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/09 20:41:00 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* ====== Ejecuta un comando simple redirigiendo stdin y stdout ====== */
void exec(char *cmd, char **env)
{
    char **args;
    char *path;

    args = ft_split(cmd, ' ');
    if (!args)
        ft_error("malloc failed");

    path = get_cmd_path(args[0], env); // reemplaza get_path
    if (!path)
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(args[0], 2);
        ft_free(args); // reemplaza ft_free_tab
        exit(127);     // Código estándar cuando el comando no existe
    }

    if (execve(path, args, env) == -1)
        ft_error("execve failed");

    ft_free(args);
}

/* ====== Ejecuta un comando dentro de un pipe ====== */
void do_pipe(char *cmd, char **env)
{
    pid_t pid;
    int pipefd[2];

    if (pipe(pipefd) == -1)
        ft_error("pipe failed");

    pid = fork();
    if (pid == -1)
        ft_error("fork failed");

    if (pid == 0)
    {
        // Hijo
        close(pipefd[0]);         // Cerrar extremo de lectura
        dup2(pipefd[1], STDOUT_FILENO); // Redirigir stdout
        exec(cmd, env);
    }
    else
    {
        // Padre
        close(pipefd[1]);         // Cerrar extremo de escritura
        dup2(pipefd[0], STDIN_FILENO);  // Redirigir stdin
        wait(NULL);
    }
}

/* ====== Manejo del here_doc ====== */
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
    {
        close(p_fd[0]); // cerrar lectura
        while (1)
        {
            char *line;
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

/* ====== Función que gestiona la apertura de archivos y here_doc ====== */
static void setup_fds(int ac, char **av, int *i, int *fd_out)
{
    if (ft_strncmp(av[1], "here_doc", 8) == 0)
    {
        if (ac < 6)
        {
            ft_putendl_fd("Usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 ... outfile", 2);
            exit(1);
        }
        *i = 3;  // Primer comando
        *fd_out = open_output_fd(av[ac - 1], 1);
        here_doc(av);
    }
    else
    {
        if (ac < 5)
        {
            ft_putendl_fd("Usage: ./pipex_bonus infile cmd1 cmd2 ... outfile", 2);
            exit(1);
        }
        *i = 2;  // Primer comando
        int fd_in = open_input_fd(av, 0);
        *fd_out = open_output_fd(av[ac - 1], 1);
        dup2(fd_in, STDIN_FILENO);
    }
}

/* ====== Main  ====== */
int main(int ac, char **av, char **env)
{
    int i, fd_out;

    setup_fds(ac, av, &i, &fd_out);

    while (i < ac - 2)
        do_pipe(av[i++], env);  // Ejecutar comandos intermedios en pipes

    dup2(fd_out, STDOUT_FILENO); // Redirigir salida del último comando
    exec(av[ac - 2], env);       // Ejecutar el último comando
    return 0;
}

//#include "pipex_bonus.h"

/**
 * @brief Ejecuta un comando simple redirigiendo stdin y stdout.
 */
/*void	command(char *cmd, char **envp, int fd_in, int fd_out)
{
	char	**args;
	char	*path;

	if (dup2(fd_in, 0) < 0 || dup2(fd_out, 1) < 0)
		ft_error("dup2 failed");
	close(fd_in);
	close(fd_out);
	args = ft_split(cmd, ' ');
	if (!args)
		ft_error("malloc failed");
	path = get_cmd_path(args[0], envp);
	if (!path)
		ft_error_cmd(args[0]);
	execve(path, args, envp);
	ft_error("execve failed");
}
*/
/** * @brief Ejecuta la lógica completa de pipex_bonus.  */
/*void	exec(int argc, char **argv, char **envp, int cmd_count, int heredoc)
{
	int		i;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];

	fd_in = open_input_fd(argv, heredoc);
	i = 0;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipefd) < 0)
			ft_error("pipe failed");
		if (fork() == 0)
		{
			fd_out = (i == cmd_count - 1) //
				? open_output_fd(argv[argc - 1], heredoc)
				: pipefd[1];
			command(argv[i + 2 + heredoc], envp, fd_in, fd_out);
		}
		close(fd_in);
		if (i < cmd_count - 1)
			fd_in = pipefd[0];
		i++;
	}
	while (wait(NULL) > 0)
		;
}*/

/**  * @brief Ejecución de múltiples comandos con soporte para here_doc.  */
/*int	main(int argc, char *argv[], char *envp[])
{
	int	heredoc;
	int	cmd_count;

	if (argc < 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 ... outfile");
	heredoc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	cmd_count = get_cmd_count(argc, heredoc);
	exec(argc, argv, envp, cmd_count, heredoc);
	return (0);
}
*/
