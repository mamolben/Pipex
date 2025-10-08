#include "pipex.h"


int main(int argc, char *argv[], char *envp[])
{
    int infile;
    int outfile;
    int pipefd[2];
    int i;

    if (argc < 5)
    {
        write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
        exit(EXIT_FAILURE);
    }
    infile = open_file_in(argv[1]);
    outfile = open_file_out(argv[argc -1]);

    if (pipe(pipefd) < 0)
        ft_error("pipe failed");

    execute_first_child(argv[2], envp, pipefd, infile);

    for (i = 3; i < argc - 2; i++)
        execute_middle_child(argv[i], envp, &pipefd);

    execute_last_child(argv[argc - 2], envp, pipefd, outfile);

    wait_for_all_commands(argc - 3);

    return 0;
}
