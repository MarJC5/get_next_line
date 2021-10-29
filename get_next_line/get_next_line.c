/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/29 12:27:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* static int	ft_strchr_pos(const char *str, int c)
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
} */

char	*ft_read_check(int fd, char **save, char *buf, char *result)
{
	char	*nl;
	char	*temp;
	int		file;

	nl = NULL;
	while (!nl)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file == -1)
			return (NULL);
		if (file != BUFFER_SIZE && file)
		{
			temp = ft_substr(buf, 0, file);
			result = ft_strjoin(*save, temp);
			printf("\n\n\033[1;33mREAD IN LOOP ->\033[0;37m\n%d", file);
			printf("\n\n\033[1;35mEND SAVE WITH REST\033[0;37m\n%s", result);
		}
		if (file == 0)
		{
			printf("\n\n\033[1;33mREAD IN LOOP ->\033[0;37m\n%d", file);
			printf("\n\n\033[1;35mEND SAVE\033[0;37m\n%s", buf);
			break ;
		}
		buf[file] = '\0';
		result = ft_strjoin(*save, buf);
		free(*save);
		*save = ft_substr(result, 0, ft_strlen(result));
		printf("\n\n\033[1;36mSAVE IN LOOP ->\033[0;37m\n%s", *save);
		nl = ft_strchr(*save, '\n');
	}
	return (result);
}

char	*ft_line(int fd, char **save, char *buf)
{
	char	*result;
	char	*temp;
	int		c;

	c = 0;
	result = NULL;
	temp = NULL;
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
