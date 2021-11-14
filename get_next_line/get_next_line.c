/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/15 00:23:11 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_ptr(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_return_line(char **save)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	tmp = NULL;
	res = NULL;
	while ((*save)[i] != '\n' && (*save)[i])
		i++;
	if ((*save)[i++] == '\n')
		res = ft_substr(*save, 0, i);
	else if (ft_strchr(*save, '\n') == NULL)
	{
		if (ft_strlen(*save) == 0 && ft_strchr(*save, '\0'))
			return (NULL);
		res = ft_strdup(*save);
	}
	tmp = ft_strdup(*save + i);
	free(*save);
	*save = tmp;
	return (res);
}

static char	*ft_read_file(int fd, char **save, char *buf)
{
	int		file;
	char	*tmp;

	file = read(fd, buf, BUFFER_SIZE);
	while (file)
	{
		buf[file] = '\0';
		if (*save)
		{
			tmp = *save;
			*save = ft_strjoin(*save, buf);
			free(tmp);
		}
		else
			*save = ft_substr(buf, 0, file);
		if (ft_strchr(buf, '\n'))
			break ;
		file = read(fd, buf, BUFFER_SIZE);
	}
	free_ptr(&buf);
	return (ft_return_line(save));
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free_ptr(&buf);
		return (NULL);
	}
	if (!save)
		save = ft_strdup("");
	ret = ft_read_file(fd, &save, buf);
	if (ret == NULL)
		free_ptr(&save);
	return (ret);
}
