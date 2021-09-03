/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:43:49 by jaehpark          #+#    #+#             */
/*   Updated: 2021/09/03 09:05:24 by jaehpark         ###   ########.fr       */
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

char *sum(char *line, char buf)
{
    int size;
    char *str;
    int i;

    size = ft_strlen(line);
    str = (char *)malloc(sizeof(char) * (size + 2));
    if (!str)
        return (NULL);
	i = 0;
    while (line[i] != 0)
    {
        str[i] = line[i];
        i++;
    }
	free(line);
    str[i++] = buf;
    str[i] = '\0';
    return (str);
}

int	get_next_line(char **line)
{
	char	buf;
	int		ret;

	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	(*line)[0] = 0;
	while ((ret = read(0, &buf, 1)) > 0)
	{
		if (buf == '\n')
			return (1);
		*line = sum(*line, buf);
		if (*line == 0)
			return (-1);
	}
	return (0);
}
