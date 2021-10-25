/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:25:47 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/25 17:24:21 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			ret;
	static char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*path;

	if (argc < 2)
	{
		ft_putendl_fd("Pleaser enter the file descriptor path after the program name.", 2);
		return (1);
	}
	else
		path = argv[argc - 1];
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putendl_fd("Cannot open the file.", 2);
		return (1);
	}
	get_next_line(fd);
	if (close(fd) == -1)
	{
		ft_putendl_fd("Error, cannot close the file.", 2);
		return (1);
	}
	return (0);
}
