#include "pipex.h"

int open_file_in(char *filename, int argc)
{
    int fd;
    if (argc < 5)
    {
        write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
        exit(EXIT_FAILURE);
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        ft_error_file(filename);
    return fd;
}

int open_file_out(char *filename, int argc)
{
    int fd;
    if (argc < 5)
    {
        write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
        exit(EXIT_FAILURE);
    }
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        ft_error_file(filename);
    return fd;
}
