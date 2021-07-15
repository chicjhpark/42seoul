/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 21:31:20 by jaehpark          #+#    #+#             */
/*   Updated: 2021/07/15 21:00:36 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_msg(char *msg)
{
	perror(msg);
	exit(1);
}

void	ft_strncpy(char *s1, char *s2, int n)
{
	int		i;

	if (s1 == NULL || s2 == NULL)
		return ;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int	find_path_idx(char **envp, char *name)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == name[j])
				j++;
			else
				break ;
		}
		if (j == 5)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*s3;
	int		len1;
	int		len2;
	int		i;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = NULL;
	s3 = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (s3 == NULL)
		return (NULL);
	ft_strncpy(s3, s1, len1);
	s3[len1++] = '/';
	i = 0;
	while (s2[i])
	{
		s3[len1 + i] = s2[i];
		i++;
	}
	s3[len1 + i] = '\0';
	return (s3);
}
