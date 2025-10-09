#include "pipex.h"

char *join_path(char *dir, char *cmd)
{
    char *tmp;
    char *result;

    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return NULL;
    result = ft_strjoin(tmp, cmd);
    free(tmp);
    return result;
}

char *find_path_env(char *envp[])
{
    int i;
    
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    return (envp[i] ? envp[i] + 5 : NULL);
}

static char *find_executable(char **paths, char *cmd)
{
    char *candidate;
    int i;
    
    i= 0;
    while (paths[i])
    {
        candidate = join_path(paths[i], cmd);
        if (candidate && access(candidate, X_OK) == 0)
            return candidate;
        free(candidate);
        i++;
    }
    return NULL;
}

char *get_cmd_path(char *cmd, char *envp[])
{
    char *path_str;
    char **paths; 
    char *result; 

    path_str = find_path_env(envp);
    paths = ft_split(path_str, ':');
    result = NULL;
    if (!cmd || !paths) 
        return NULL;
    result = find_executable(paths, cmd);
    ft_free(paths);
    return result;
}
