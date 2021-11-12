/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/12 08:01:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_return_line(char **save)
{
	char	*tmp;
	char	*res;
	int		nl;
	int		endl;

	tmp = NULL;
	res = NULL;
	nl = ft_strchr_pos(*save, '\n');
	endl = ft_strchr_pos(*save, '\0');
	if (nl <= 0)
	{
		if (endl <= 0)
			return (NULL);
		res = ft_substr(*save, 0, ft_strlen(*save));
		free(*save);
		*save = NULL;
		return (res);
	}
	res = ft_substr(*save, 0, nl + 1);
	tmp = ft_substr(*save, ft_strlen(res), endl);
	printf("\nREST:\033[1;32m %s\033[0m\n", tmp);
	free(*save);
	*save = tmp;
	return (res);
}

static void	ft_read_file(int fd, char **save, char *buf)
{
	int		file;
	char	*tmp;

	file = read(fd, buf, BUFFER_SIZE);
	while (file > 0)
	{
		buf[file] = 0;
		if (ft_strchr_pos(*save, '\n') >= 0)
			break ;
		tmp = *save;
		*save = ft_strjoin(*save, buf);
		free(tmp);
		file = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
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
	ft_read_file(fd, &save, buf);
	return (ft_return_line(&save));
}
