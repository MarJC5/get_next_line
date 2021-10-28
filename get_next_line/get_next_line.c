/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/29 00:12:43 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchr_pos(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) + 1)
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_read_check(int fd, char **save, char *buf, char *result)
{
	char	*nl;
	int		file;

	nl = NULL;
	while (!nl)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file <= 0)
		{
			printf("\n\033[1;31mEND FILE\033[0;37m\n\n");
			return (NULL);
		}
		buf[file] = '\0';
		result = ft_strjoin(*save, buf);
		free(*save);
		*save = ft_substr(result, 0, ft_strlen(result));
		nl = ft_strchr(*save, '\n');
	}
	return (result);
}

static char	*ft_line(int fd, char **save, char *buf)
{
	char	*result;
	char	*temp;
	int		c;

	c = 0;
	result = ft_read_check(fd, save, buf, result);
	while (result[c] != '\n')
		c++;
	result[c] = '\0';
	free(temp);
	temp = ft_substr(*save, c + 1, BUFFER_SIZE - c);
	free(*save);
	*save = ft_substr(temp, 0, ft_strlen(temp));
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

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
