/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:13:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/08/13 21:37:17 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	debug(t_cmd *cmd)
{
	int		i;
	int		j;

	printf("infile : %s\n", cmd->infile);
	printf("outfile : %s\n", cmd->outfile);
	i = 0;
	while (cmd->cmd[i])
	{
		printf("cmd %d : ", i);
		j = 0;
		while (cmd->cmd[i][j])
		{
			printf("%s ", cmd->cmd[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("-------------------------------------\n");
	printf("%s\n", cmd->data);
	printf("-------------------------------------\n");
	i = 0;
	while (cmd->path[i])
	{
		printf("path : %s\n", cmd->path[i]);
		i++;
	}
}

void	exe_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_msg("pipe");
	pid = fork();
	if (pid > 0)
	{
		wait(0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(cmd->fd[1], 1);
		if (cmd->num > 1)
		{
			if (pipe(fd) == -1)
				exit_msg("pipe");
			while (cmd->num > 1)
			{
				pid = fork();
				if (pid > 0)
				{
					wait(0);
					execve(cmd->path[cmd->num], cmd->cmd[cmd->num], 0);
					cmd->num--;
				}
				else if (pid == 0)
				{
					execve(cmd->path[cmd->num], cmd->cmd[cmd->num], 0);
					cmd->num--;
				}
				else
					exit_msg("fork");
			}
		}
		else if (cmd->num == 1)
			execve(cmd->path[1], cmd->cmd[1], 0);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		dup2(cmd->fd[0], 0);
		execve(cmd->path[0], cmd->cmd[0], 0);
	}
	else
		exit_msg("fork");
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	if (argc >= 5)
	{
		ft_memset(&cmd, 0, sizeof(cmd));
		parse_file(&cmd, argc, argv);
		parse_cmd(&cmd, argc, argv);
		parse_path(&cmd, envp);
		exe_cmd(&cmd);
	}
	else
		exit_msg("Invalid format");
	return (0);
}
