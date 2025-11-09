/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:47:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/09 19:48:39 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ====== Une la ruta de archivo y comando ====== */
char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	return (result);
}

/* ====== Busca un camino ======*/
char	*find_path_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		return (envp[i] + 5);
	else
		return (NULL);
}

/* ====== Busca ejecutable en las rutas ====== */
static char	*find_executable(char **paths, char *cmd)
{
	char	*candidate;
	int		i;

	i = 0;
	while (paths[i])
	{
		candidate = join_path(paths[i], cmd);
		if (candidate && access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

/* ====== Obtener la ruta del comando ====== */
char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*path_str;
	char	**paths;
	char	*result;

	path_str = find_path_env(envp);
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	if (!paths)
		return (NULL);
	result = find_executable(paths, cmd);
	ft_free(paths);
	return (result);
}
