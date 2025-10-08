##include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void process_child(char *argv[], char *envp[], int pipefd[], int infile)
{
    char **cmd_args;
    char *cmd_path;

    if (dup2(infile, STDIN_FILENO) < 0)
        ft_error("dup2 failed");
    if (dup2(pipefd[1], STDOUT_FILENO) < 0)
        ft_error("dup2 failed");
    close(pipefd[0]);
    close(infile);
    cmd_args = ft_split(argv[2], ' ');
    if (!cmd_args)
        ft_error("malloc failed");
    cmd_path = get_cmd_path(cmd_args[0], envp);
    if (!cmd_path)
        ft_error_cmd(cmd_args[0]);
    execve(cmd_path, cmd_args, envp);
    ft_error("execve failed");
}

void process_parent(char *argv[], char *envp[], int pipefd[], int outfile)
{
    char **cmd_args;
    char *cmd_path;

    if (dup2(pipefd[0], STDIN_FILENO) < 0)
        ft_error("dup2 failed");
    if (dup2(outfile, STDOUT_FILENO) < 0)
        ft_error("dup2 failed");
    close(pipefd[1]);
    close(outfile);
    cmd_args = ft_split(argv[3], ' ');
    if (!cmd_args)
        ft_error("malloc failed");
    cmd_path = get_cmd_path(cmd_args[0], envp);
    if (!cmd_path)
        ft_error_cmd(cmd_args[0]);
    execve(cmd_path, cmd_args, envp);
    ft_error("execve failed");
}

int main(int argc, char *argv[], char *envp[])
{
    int infile;
    int outfile;
    int pipefd[2];
    pid_t pid;

    ft_error_argc(argc);
    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
        ft_error_file(argv[1]);
    outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfile < 0)
    {
        close(infile);
        ft_error_file(argv[4]);
    }
    if (pipe(pipefd) < 0)
        ft_error("Pipe creation failed");
    pid = fork();
    if (pid < 0)
        ft_error("Fork failed");
    if (pid == 0)
        process_child(argv, envp, pipefd, infile);
    wait(NULL);
    process_parent(argv, envp, pipefd, outfile);
    return (0);
}
