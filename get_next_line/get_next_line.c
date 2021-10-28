/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/28 17:41:55 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_check(int fd, char **save, char *buf, char *result)
{
	int		file;
	int		i;

	i = 0;
	printf("\n\n===== SAVE UP =====\n%s\n\n", *save);
	while (!ft_strchr(*save, '\n'))
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file == -1)
			return (NULL);
		buf[file] = '\0';
		result = ft_strjoin(*save, buf);
		free(*save);
		*save = ft_substr(result, 0, ft_strlen(result));
		printf("\n\n===== SAVE IN =====\n%s\n\n", *save);
		printf("\n\n===== SAVE NL =====\n%d\n\n", ft_strchr_pos(*save, '\n'));
	}
	return (result);
}

static char	*ft_line(int fd, char **save, char *buf)
{
	char	*result;
	char	*temp;
	int		c;
	int		i;

	c = 0;
	i = 0;
	ft_read_check(fd, save, buf, result);
	result = buf;
	while (result[c] != '\n')
		c++;
	result[c] = '\0';
	temp = ft_substr(*save, c + 1, BUFFER_SIZE - c);
	printf("\n\n===== TEMP =====\n%s\n\n", temp);
	free(*save);
	*save = ft_substr(temp, 0, ft_strlen(temp));
	printf("\n\n===== SAVE OUT =====\n%s\n\n", *save);
	printf("\n\n===== RESULT =====\n");
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

	i = 2;
	if (argc != 2)
		printf("Please enter the file descriptor path after the program name.\n");
	else
		path = argv[argc - 1];
	if ((fd = open(path, O_RDONLY)) == -1)
		printf("Cannot open the file.\n");
	result = get_next_line(fd);
	while (i--)
	{
		printf("%s", result);
		result = get_next_line(fd);
	}
	if (close(fd) == -1)
		printf("Error, cannot close the file.\n");
	return (0);
}
