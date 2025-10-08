#include "pipex.h"

void	ft_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	ft_error_cmd(const char *cmd)
{
    write(2, cmd, ft_strlen(cmd));
    write(2, ": command not found\n", 20);
    exit(127);
}

void	ft_error_file(const char *file)
{
    write(2, file, ft_strlen(file));
    write(2, ": No such file or directory\n", 28);
    exit(1);
}

void	ft_error_argc(int argc)
{
    if (argc != 5)
    {
        write(2, "Usage: ./pipex infile cmd1, cmd2 outfile\n", 40);
        exit(EXIT_FAILURE);
    }
}