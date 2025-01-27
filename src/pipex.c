/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:37:42 by hdelacou          #+#    #+#             */
/*   Updated: 2025/01/14 18:40:40 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: error executing command: ", 2);
		ft_putendl_fd(cmd, 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void	child_process(char **av, int *pipe_fd, char **env)
{
	int	fd_infile;

	fd_infile = open_file(av[1], 0);
	dup2(fd_infile, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execute_cmd(av[2], env);
	exit(1);
}

void	parent_process(char **av, int *pipe_fd, char **env)
{
	int	fd_outfile;

	fd_outfile = open_file(av[4], 1);
	dup2(fd_outfile, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	execute_cmd(av[3], env);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child_process(av, pipe_fd, env);
	parent_process(av, pipe_fd, env);
}
