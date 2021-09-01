/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:43:49 by jaehpark          #+#    #+#             */
/*   Updated: 2021/09/02 05:57:34 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *msg)
{
	perror(msg);
	exit(1);
}

char	*find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = NULL;
		path = ft_strjoin(paths[i], "/");
		temp = path;
		path = ft_strjoin(path, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free(paths);
			return (path);
		}
		i++;
	}
	return (NULL);
}

/*int	get_next_line(char **line)
{
	char	buf;
	int		ret;
	char	*temp;

	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	(*line)[0] = 0;
	while ((ret = read(0, &buf, 1)) > 0)
	{
		if (buf == '\n')
			return (1);
		temp = *line;
		*line = ft_strjoin(*line, &buf);
		free(temp);
		if (*line == 0)
			return (-1);
	}
	if (ret == -1)
		return (-1);
	else
		return (0);
}*/

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	//free(buffer);
	return (r);
}