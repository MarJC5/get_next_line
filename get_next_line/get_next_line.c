/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/03 11:53:03 by jmartin          ###   ########.fr       */
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
	if (nl)
	{
		tmp = ft_substr(*save, 0, ft_strchr_pos(*save, '\n') + 1);
		*save = ft_substr(*save, ft_strlen(tmp), ft_strlen(*save) + 1);
	}
	else if (endl)
	{
		tmp = ft_substr(*save, 0, ft_strchr_pos(*save, '\0'));
		*save = ft_substr(*save, ft_strlen(tmp), ft_strlen(*save));
	}
	return (tmp);
}

static char	*ft_read_file(int fd, char **save, char *buf)
{
	int		file;
	char	*result;

	file = 1;
	while (file != 0)
	{
		file = read(fd, buf, BUFFER_SIZE);
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
	}
	return (ft_return_line(save));
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

	buf = NULL;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	if (!save)
		return (NULL);
	ret = ft_read_file(fd, &save, buf);
	free(buf);
	buf = NULL;
	return (ret);
}

/*
* 1. Check fd & BUFFER_SIZE is valid ?
* 2. Init static and buf malloc
* 3. Save file regarding BUFFER_SIZE and check if \n is in it
* 4. If no \n is founded, join static with new buf value
* 5. Redo until \n is founded
* 6. If \n is found return the line and then free the static > go back to 3.
*/
