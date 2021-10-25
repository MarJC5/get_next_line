/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:26:20 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/25 16:23:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* Writes functions
* ft_putchar_fd / ft_putstr_fd / ft_putendl_fd / ft_putnbr_fd
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
		ft_putchar_fd(str[i++], fd);
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}

/*
* Others functions
* ft_strjoin
*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*sdst;
	const char	*ssrc;
	size_t		i;

	i = -1;
	sdst = (char *)dst;
	ssrc = (const char *)src;
	if (!sdst && !ssrc)
		return (NULL);
	while (++i < n)
		sdst[i] = ssrc[i];
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		prefix;
	int		suffix;
	int		full;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	prefix = ft_strlen(s1);
	suffix = ft_strlen(s2);
	full = prefix + suffix;
	str = malloc((prefix + suffix + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1 && s2)
	{
		ft_memcpy(str, s1, prefix);
		ft_memcpy(str + prefix, s2, suffix);
	}
	str[full] = '\0';
	return ((char *)str);
}
