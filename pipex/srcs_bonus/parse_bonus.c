/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 21:40:22 by jaehpark          #+#    #+#             */
/*   Updated: 2021/08/09 18:31:02 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_cmd(t_cmd *cmd, int argc, char **argv)
{
	int		i;

	cmd->cmd = NULL;
	cmd->cmd = (char ***)malloc(sizeof(char **) * (argc - 3 + 1));
	cmd->path = (char **)malloc(sizeof(char *) * (argc - 3 + 1));
	if (cmd->cmd == NULL)
		exit_msg("malloc");
	i = 0;
	while (i + 2 < argc - 1)
	{
		cmd->cmd[i] = ft_split(argv[i + 2], ' ');
		if (cmd->cmd[i] == NULL)
			exit_msg("malloc");
		i++;
	}
	cmd->num = i - 1;
	cmd->cmd[i] = NULL;
}

void	parse_path(t_cmd *cmd, char **envp)
{
	char	**temp;
	char	*path;
	int		i;
	int		j;
	int		k;

	i = find_path_idx(envp, "PATH=");
	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		j++;
	temp = ft_split(&envp[i][j + 1], ':');
	i = -1;
	k = -1;
	while (cmd->cmd[++i])
	{
		j = -1;
		while (temp[++j])
		{
			path = ft_strcat(temp[j], cmd->cmd[i][0]);
			if (path == NULL)
				exit_msg("malloc");
			if (access(path, F_OK) == 0)
				cmd->path[++k] = path;
		}
	}
	cmd->path[k + 1] = NULL;
}

void	parse_infile(t_cmd *cmd)
{
	char	*temp;
	char	buf;
	int		ret;

	cmd->fd[0] = open(cmd->infile, O_RDONLY);
	if (cmd->fd[0] < 0)
		exit_msg("open");
	cmd->data = NULL;
	while ((ret = read(cmd->fd[0], &buf, 1)) > 0)
	{
		temp = cmd->data;
		cmd->data = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 2));
		cmd->data[0] = '\0';
		if (cmd->data == NULL)
			exit_msg("malloc");
		ft_strncpy(cmd->data, temp, ft_strlen(temp));
		if (temp != NULL)
			free(temp);
		ret = ft_strlen(cmd->data);
		cmd->data[ret] = buf;
		cmd->data[ret + 1] = '\0';
	}
	if (ret < 0)
		exit_msg("read data");
}

void	parse_file(t_cmd *cmd, int argc, char **argv)
{
	cmd->infile = argv[1];
	cmd->outfile = argv[argc - 1];
	if (access(cmd->infile, F_OK) < 0)
		exit_msg(cmd->infile);
	if (access(cmd->infile, R_OK) < 0)
		exit_msg("read");
	parse_infile(cmd);
	if (access(cmd->outfile, F_OK) == 0 && access(cmd->outfile, W_OK) < 0)
		exit_msg("write");
	cmd->fd[1] = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd[1] < 0)
		exit_msg("open");
}
