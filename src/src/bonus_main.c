/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/19 18:23:04 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

void	check_args(t_pipex *px)
{
	if (px->argc < 5)
	{
		write(2, "Usage: ./pipex_bonus [here_doc LIMITER] cmd1 ... cmdN outfile\n", 63);
		exit(EXIT_FAILURE);
	}
	px->is_heredoc = (ft_strcmp(px->argv[1], "here_doc") == 0);
}


void	init_files(t_pipex *px)
{
	if (px->is_heredoc)
	{
		px->infile = create_heredoc_file(px->argv[2]);
		px->outfile = open(px->argv[px->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		px->infile = open_file_in(px->argv[1]);
		px->outfile = open_file_out(px->argv[px->argc - 1]);
	}
	if (px->infile < 0 || px->outfile < 0)
		exit(EXIT_FAILURE);
}

int	**init_pipes(int cmd_count)
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
			ft_error("pipe failed");
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

/*static void	spawn_children(int cmd_count, char *argv[], char *envp[],
			int **pipes, int infile, int outfile)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < cmd_count - 1)
	{
		pid = fork();
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
}*/
void	spawn_children(t_pipex *px)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < px->cmd_count)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork failed");
		if (pid == 0)
			child_process(px, i);
		i++;
	}
}

void	child_process(t_pipex *px, int i)
{
	if (i == 0)
		execute_first_child(px, i);
	else if (i == px->cmd_count - 1)
		execute_last_child(px, i);
	else
		execute_middle_child(px, i);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	px;

	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	check_args(&px);
	init_files(&px);
	px.cmd_count = px.argc - 3 - px.is_heredoc;
	px.pipes = init_pipes(px.cmd_count);
	spawn_children(&px);
	free_pipes(px.pipes, px.cmd_count);
	close(px.infile);
	close(px.outfile);
	wait_for_all(px.cmd_count);
	return (0);
}