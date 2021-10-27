/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/27 17:41:42 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *save, char *buf)
{
	char	*result;
	char	*nl;
	int		file;
	int		c;

	c = 0;
	nl = NULL;
	while (!nl)
	{
		file = read(fd, buf, BUFFER_SIZE);
		if (file == -1)
			return (NULL);
		buf[file] = '\0';
		if (save)
			result = ft_strjoin(save, buf);
		else
			result = ft_substr(buf, 0, file);
		printf("\n===== SAVE INSIDE =====\n%s\n", save);
		printf("\n===== STRJOIN =====\n%s\n", result);
		free(save);
		save = result;
		//printf("\n===== LOOP NEW LINE =====\n%s\n", *save);
		nl = ft_strchr(buf, '\n');
	}
	while (result[c] != '\n')
		c++;
	result[c] = '\0';
	save = ft_substr(save, c + 1, BUFFER_SIZE - c);
	printf("\n===== SAVE OUTSIDE =====\n%s\n", save);
	printf("\n===== RESULT =====\n");
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buf;
	char			*ret;

	if (fd > 0 && BUFFER_SIZE > 0)
		buf = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	ret = ft_read_line(fd, save, buf);
	free(buf);
	return (ret);
}

int	main(int argc, char *argv[])
{
	int		i;
	int		fd;
	char	*path;
	char	*result;

	i = 1;
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
