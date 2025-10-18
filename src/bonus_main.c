/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/18 21:09:13 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

static void	check_args(int argc)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus infile cmd1 ... cmdN outfile\n", 51);
		exit(EXIT_FAILURE);
	}
}

static int	**init_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		ft_error("malloc failed");
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			ft_error("malloc failed");
		if (pipe(pipes[i]) == -1)
			ft_error("Pipe creation failed");
		i++;
	}
	return (pipes);
}

static void	free_pipes(int **pipes, int cmd_count)
{
	int	i;
	
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void spawn_children(int cmd_count, char *argv[], char *envp[],
	int **pipes, int infile, int outfile)
{
	int	i;
    
	i = 0;
	while (i < cmd_count - 1)
	{
		pid_t pid = fork();
		if (pid < 0)
			ft_error("Fork failed");
		if (pid == 0)
		{
			if (i == 0)
				execute_first_child(argv[2], envp, pipes[0], infile);
			else if (i == cmd_count - 1)
				execute_last_child(argv[argc - 2], envp, pipes[i - 1], outfile);
			else
				execute_middle_child(argv[i + 2], envp, pipes[i - 1], pipes[i]);
        }
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	cmd_count;
	int	infile;
	int	outfile;
	int	**pipes;

	check_args(argc);
	cmd_count = argc - 3;
	infile = open_file_in(argv[1], argc);
	outfile = open_file_out(argv[argc - 1], argc);
	pipes = init_pipes(cmd_count);
	spawn_children(cmd_count, argv, envp, pipes, infile, outfile);
	free_pipes(pipes, cmd_count);
	close(infile);
	close(outfile);
	wait_for_all(cmd_count);
	return (0);
}
