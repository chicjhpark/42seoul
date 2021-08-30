/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 20:20:45 by jaehpark          #+#    #+#             */
/*   Updated: 2021/08/30 12:07:26 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		infile;
	char	**cmd;

	if (access(argv[1], F_OK | R_OK) == -1)
		error_msg("exist or read");
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_msg("open");
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	cmd = ft_split(argv[2], ' ');
	if (execve(find_path(envp, cmd[0]), cmd, 0) == -1)
		error_msg("exe");
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		outfile;
	char	**cmd;

	wait(0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error_msg("open");
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	cmd = ft_split(argv[3], ' ');
	if (execve(find_path(envp, cmd[0]), cmd, 0) == -1)
		error_msg("exe");
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error_msg("pipe");
		pid = fork();
		if (pid == 0)
			child_process(argv, envp, fd);
		else if (pid > 0)
			parent_process(argv, envp, fd);
		else
			error_msg("fork");
		close(fd[0]);
		close(fd[1]);
	}
	else
		error_msg("Invalid argument.");
	return (0);
}
