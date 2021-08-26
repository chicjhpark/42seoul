/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 20:20:45 by jaehpark          #+#    #+#             */
/*   Updated: 2021/08/26 23:01:02 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		infile;
	char	**temp;
	char	*cmd[3];

	if (access(argv[1], F_OK | R_OK) == -1)
		error_msg("exist or read");
	infile = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_msg("open");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	temp = ft_split(argv[2], ' ');
	cmd[0] = find_path(envp, temp[0]);
	cmd[1] = temp[1];
	cmd[2] = NULL;
	if (execve(cmd[0], cmd, 0) == -1)
		error_msg("exe");
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		outfile;
	char	**temp;
	char	*cmd[3];

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error_msg("open");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	temp = ft_split(argv[3], ' ');
	cmd[0] = find_path(envp, temp[0]);
	cmd[1] = temp[1];
	cmd[2] = NULL;
	if (execve(cmd[0], cmd, 0) == -1)
		error_msg("exe");
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error_msg("pipe");
		pid = fork();
		if (pid == 0)
			child_process(argv, envp, fd);
		else if (pid > 0)
		{
			wait(0);
			parent_process(argv, envp, fd);
			close(fd[0]);
			close(fd[1]);
		}
		else
			error_msg("fork");
	}
	else
		error_msg("Invalid argument.");
	return (0);
}
