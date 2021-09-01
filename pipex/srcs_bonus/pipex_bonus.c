/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:44:18 by jaehpark          #+#    #+#             */
/*   Updated: 2021/09/02 06:04:23 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	parse_file(int argc, char **argv, int flag)
{
	int	infile;
	int	outfile;

	if (flag == 0)
	{
		if (access(argv[1], F_OK | R_OK) == -1)
			error_msg("exist or read");
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
			error_msg("open");
		dup2(infile, STDIN_FILENO);
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		error_msg("open");
	return (outfile);
}

void	exe_cmd(char *argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**cmd;

	if (pipe(fd) == -1)
		error_msg("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		cmd = ft_split(argv, ' ');
		if (execve(find_path(envp, cmd[0]), cmd, envp) == -1)
			error_msg("exe");
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	else
		error_msg("fork");
}

void	here_doc(int argc, char *limiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	if (argc < 6)
		error_msg("Invalid format.");
	if (pipe(fd) == -1)
		error_msg("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		outfile;
	char	**cmd;

	if (argc >= 5)
	{
		i = 2;
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i++;
			outfile = parse_file(argc, argv, 1);
			here_doc(argc, argv[2]);
		}
		else
			outfile = parse_file(argc, argv, 0);
		while (i < argc - 2)
			exe_cmd(argv[i++], envp);
		dup2(outfile, STDOUT_FILENO);
		cmd = ft_split(argv[argc - 2], ' ');
		if (execve(find_path(envp, cmd[0]), cmd, envp) == -1)
			error_msg("exe");
	}
	else
		error_msg("Invalid format.");
	return (0);
}
