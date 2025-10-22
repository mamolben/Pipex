/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:28:34 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/20 20:44:01 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_args(int argc)
{
	if (argc < 5)
	{
		write(2, "Usage: ./pipex_bonus [here_doc LIMITER] cmd1 ... cmdN outfile\n", 63);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		filein;
	int		fileout;
	int		**pipes;
	int		cmd_count;
	int		is_heredoc;

	check_args(argc);
	is_heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		is_heredoc = 1;

	if (is_heredoc)
	{
		filein = create_heredoc_file(argv[2]);
		fileout = open_file_out(argv[argc - 1], 1, argc);
		cmd_count = argc - 4;
		i = 0;
	}
	else
	{
		filein = open_file_in(argv[1], argc);
		fileout = open_file_out(argv[argc - 1], 0, argc);
		cmd_count = argc - 3;
		i = 0;
	}

	pipes = init_pipes(cmd_count);

	while (i < cmd_count)
	{
		if (i == 0)
			child_process_first(argv, envp, pipes[i], filein, is_heredoc);
		else if (i == cmd_count - 1)
			child_process_last(argv, envp, pipes[i - 1], fileout, i, is_heredoc);
		else
			child_process_middle(argv, envp, pipes[i - 1], pipes[i], i, is_heredoc);
		i++;
	}

	free_pipes(pipes, cmd_count);
	wait_for_all(cmd_count);
	return (0);
}


