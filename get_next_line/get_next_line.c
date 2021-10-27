/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/27 07:48:28 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*str;
	char			buf[BUFFER_SIZE + 1];
	int				ret;
	int				i;

	i = 0;
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (buf[i] != '\n' && i < ft_strlen(buf))
		{
			printf("%s", buf - i++);
		}
	}
	return (str);
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
	while (result != NULL)
	{
		printf("%3i:%s", i, result);
		i++;
		result = get_next_line(fd);
	}
	if (close(fd) == -1)
		printf("Error, cannot close the file.\n");
	return (0);
}
