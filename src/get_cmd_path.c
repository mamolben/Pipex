#include "pipex.h"

void	ft_free(char **str)
{
    int	pos;

    pos = 0;
    while (str[pos])
    {
        free(str[pos]);
        pos++;
    }
    free(str);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n && (str1[i] || str2[i]))
    {
        if (str1[i] != str2[i])
            return ((unsigned char)str1[i] - (unsigned char)str2[i]);
        i++;
    }
    return (0);
}

char *join_path(char *dir, char *cmd)
{
    char *path;
    size_t d;
    size_t c;
    size_t n;

    d = ft_strlen(dir);
    c = ft_strlen(cmd);
    n = d + c + 2;
    path = malloc(n);
    if (!path)
        return (NULL);
    n = 0;
    while (dir[n])
    {
        path[n] = dir[n];
        n++;
    }
    path[n] = '/';
    n++;
    c = 0;
    while (cmd[c])
    {
        path[n] = cmd[c];
        n++;
        c++;
    }
    path[n] = '\0';
    return (path);
}

char *get_cmd_path(char *cmd, char *envp[])
{
    int i;
    char **paths;
    char *result;

    i = 0;
    if (!cmd)
        return (NULL);
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PATH=", 5))
            break;
        i++;
    }
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        result = join_path(paths[i], cmd);
        if (result)
		{
            if (access(result, X_OK) == 0)
            {
                ft_free(paths);
                return (result);
            }
            free(result);
		}
        i++;
    }
    ft_free(paths);
    return (NULL);
}
