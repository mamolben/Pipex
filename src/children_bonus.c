#include "pipex.h"

void execute_first_child(char *cmd, char *envp[], int pipefd[2], int infile)
{
    if (dup2(infile, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
        ft_error("dup2 failed");
    close(pipefd[0]);
    close(infile);
    exec_cmd(cmd, envp);
}

void execute_middle_child(char *cmd, char *envp[], int pipefd_prev[2], int pipefd_next[2])
{
    if (dup2(pipefd_prev[0], STDIN_FILENO) < 0 || dup2(pipefd_next[1], STDOUT_FILENO) < 0)
        ft_error("dup2 failed");
    close(pipefd_prev[1]);
    close(pipefd_next[0]);
    exec_cmd(cmd, envp);
}

void execute_last_child(char *cmd, char *envp[], int pipefd[2], int outfile)
{
    if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
        ft_error("dup2 failed");
    close(pipefd[1]);
    close(outfile);
    exec_cmd(cmd, envp);
}

void wait_for_all(int n)
{
    int i;
    for (i = 0; i < n; i++)
        wait(NULL);
}

static void exec_cmd(char *cmd, char *envp[])
{
    char **cmd_args = ft_split(cmd, ' ');
    char *cmd_path;

    if (!cmd_args)
        ft_error("malloc failed");
    cmd_path = get_cmd_path(cmd_args[0], envp);
    if (!cmd_path)
        ft_error_cmd(cmd_args[0]);
    if (execve(cmd_path, cmd_args, envp) == -1)
        ft_error("execve failed");
}
