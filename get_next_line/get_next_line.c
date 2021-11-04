/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/04 16:03:08 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static char	*ft_return_line(char **save)
{
	char	*tmp;
	int		nl;
	int		endl;

	tmp = NULL;
	nl = ft_strchr_pos(*save, '\n');
	endl = ft_strchr_pos(*save, '\0');
	if (nl >= 0)
	{
		tmp = ft_substr(*save, 0, ft_strchr_pos(*save, '\n') + 1);
		free(*save);
		*save = ft_substr(*save, ft_strlen(tmp), ft_strlen(*save));
	}
	else if (endl)
	{
		tmp = ft_substr(*save, 0, ft_strchr_pos(*save, '\0'));
		free(*save);
		*save = ft_substr(*save, ft_strlen(tmp), ft_strlen(*save));
	}
	return (tmp);
}

static char	*ft_read_file(int fd, char **save, char *buf)
{
	int		nl;
	int		file;
	char	*result;

	nl = ft_strchr_pos(*save, '\n');
	while (nl <= 0)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file == 0)
			break ;
		if (file < 0)
			return (NULL);
		if (file != 0)
		{
			buf[file] = '\0';
			result = ft_strjoin(*save, buf);
			free(*save);
			*save = ft_strdup(result);
			free(result);
			result = NULL;
		}
		nl = ft_strchr_pos(*save, '\n');
	}
	return (ft_return_line(save));
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	ret = ft_read_file(fd, &save, buf);
	if (ret == NULL)
	{
		free(save);
		save = NULL;
	}
	free(buf);
	buf = NULL;
	return (ret);
}
