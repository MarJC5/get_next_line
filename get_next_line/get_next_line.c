/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/30 15:12:43 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nl_end(char *result, char **save)
{
	char	*temp;
	int		c;
	int		i;

	c = 0;
	temp = NULL;
	if (ft_strchr_pos(result, '\n'))
	{
		while (result[c] != '\n')
			c++;
		result[c + 1] = '\0';
		temp = ft_substr(*save, c - 1, BUFFER_SIZE - c);
		free(temp);
	}
	if (result[ft_strlen(result)] == '\0')
	{
		i = 0;
		while (result[c++] != '\0')
			i++;
		temp = ft_substr(*save, c - 1, c - (BUFFER_SIZE + i));
		free(temp);
	}
	*save = ft_substr(temp, 0, ft_strlen(temp));
	return (*save);
}

char	*ft_read_check(int fd, char **save, char *buf, char *result)
{
	char	*nl;
	int		file;

	nl = NULL;
	while (!nl)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file <= 0)
		{
			result = ft_substr(*save, 0, ft_strlen(*save));
			break ;
		}
		if (file == -1)
			return (NULL);
		buf[file] = '\0';
		free(result);
		result = ft_strjoin(*save, buf);
		free(*save);
		*save = ft_substr(result, 0, ft_strlen(result));
		nl = ft_strchr(*save, '\n');
	}
	return (result);
}

char	*ft_line(int fd, char **save, char *buf)
{
	char	*result;

	result = NULL;
	result = ft_read_check(fd, save, buf, result);
	ft_nl_end(result, save);
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

	buf = NULL;
	if (fd > 0 && BUFFER_SIZE > 0)
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (!save)
		save = malloc(1);
	if (!save)
		return (NULL);
	ret = ft_line(fd, &save, buf);
	free(buf);
	return (ret);
}
