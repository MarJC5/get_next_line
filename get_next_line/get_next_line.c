/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/29 00:10:26 by jmartin          ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int		i;
	int		fd;
	char	*path;
	char	*result;

	i = 0;
	if (argc != 2)
		printf("Please enter the file descriptor path after the program name.\n");
	else
		path = argv[argc - 1];
	if ((fd = open(path, O_RDONLY)) == -1)
		printf("Cannot open the file.\n");
	result = get_next_line(fd);
	while (i++ < 10)
	{
		printf("\n\033[1;32mRESULT -> \033[0;37m\033[1;37mline N°%d\033[0;37m\n", i);
		printf("%s\n", result);
		result = get_next_line(fd);
	}
	if (close(fd) == -1)
		printf("Error, cannot close the file.\n");
	return (0);

	//printf("\n\n\033[1;37mTEMP ->\033[0;37m\n%s", temp);

	//printf("\n\n\033[1;33mSAVE NL POSITION ->\033[0;37m\n%d", ft_strchr_pos(*save, '\n'));

	//printf("\n\n\033[1;34mSAVE BEFORE LOOP ->\033[0;37m\n%s", *save);
	//printf("\n\n\033[1;36mSAVE IN LOOP ->\033[0;37m\n%s", *save);

	//printf("\n\n\033[1;31mBUF IN LOOP ->\033[0;37m\n%s", buf);
	//printf("\n\n\033[1;33mBUF AFTER LOOP ->\033[0;37m\n%s", result);
}
