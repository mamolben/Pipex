/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:01:28 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/02 16:02:12 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "pipex.h" 	

void execute_cmd(char *argv, char **envp)
{
    char **cmd; 
    char *path; 

    cmd = NULL; 
    path = NULL;
    cmd = ft_split(argv, ' '); //Divide la cadena argv en un array de cadenas usando espacio como delimitador
    if (!cmd) //Si no se pudo asignar memoria para cmd
        exit_error("Error: Memory allocation failed\n"); //manejo de error
    path = get_path(cmd[0], envp); //Obtiene la ruta del comando
    if (!path) //Si no se encuentra la ruta del comando
    {
        free_matrix(cmd);
        exit_error("Error: Command not found\n");
    }
    if (execve(path, cmd, envp) == -1)
    {
        free(path);
        free_matrix(cmd);
        exit_error("Error: execve failed\n");
    }
}

char *get_path(char *cmd, char **envp)
{
    char **paths;
    char *full_path;
    int i;

    i = 0;
    while (envp[i] && strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return NULL;
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        exit_error("Error: Memory allocation failed\n");
    i = 0;
    while (paths[i])
    {
        full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
        if (!full_path)
        {
            free_matrix(paths);
            exit_error("Error: Memory allocation failed\n");
        }
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free_matrix(paths);
            return full_path;
        }
        free(full_path);
        i++;
    }
    free_matrix(paths);
    return NULL;
}

void free_matrix(char **matrix)
{
    int i;

    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}