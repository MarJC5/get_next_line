/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:26:08 by jmartin           #+#    #+#             */
/*   Updated: 2021/11/02 17:10:18 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_line(int fd, char **save, char *buf);
char	*ft_read_check(int fd, char **save, char *buf, char *result);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);

int		ft_strchr_pos(const char *str, int c);

size_t	ft_strlen(const char *str);

#endif
