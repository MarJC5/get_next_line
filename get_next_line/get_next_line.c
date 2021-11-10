/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/10 17:22:22 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_return_line(char **save, int nl, int endl)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	if (nl >= 0)
	{
		res = ft_substr(*save, 0, nl + 1);
		tmp = ft_substr(*save, ft_strlen(res), endl);
		free(*save);
		*save = ft_strdup(tmp);
	}
	else if (endl)
	{
		res = ft_substr(*save, 0, endl);
		free(*save);
		*save = NULL;
	}
	free(tmp);
	tmp = NULL;
	return (res);
}

static char	*ft_read_file(int fd, char **save, char *buf)
{
	int		file;
	int		endl;
	int		nl;
	char	*tmp;

	file = read(fd, buf, BUFFER_SIZE);
	while (file > 0)
	{
		buf[file] = 0;
		tmp = *save;
		*save = ft_strjoin(*save, buf);
		free(tmp);
		if (ft_strchr_pos(buf, '\n') >= 0)
			break ;
		file = read(fd, buf, BUFFER_SIZE);
	}
	nl = ft_strchr_pos(*save, '\n');
	endl = ft_strchr_pos(*save, '\0');
	return (ft_return_line(save, nl, endl));
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
