/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:13:08 by jaehpark          #+#    #+#             */
/*   Updated: 2021/07/14 16:20:05 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int		main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	if (argc > 2)
	{
		ft_memset(&cmd, 0, sizeof(cmd));
		parse_file(&cmd, argc, argv);
		parse_cmd(&cmd, argc, argv);
		parse_path(&cmd, envp);
		exe_cmd(&cmd);
		debug(&cmd);
	}
	return (0);
}
