/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:26:20 by jmartin           #+#    #+#             */
/*   Updated: 2021/10/27 10:47:18 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) + 1)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*s;

	i = -1;
	if (!str)
		return (NULL);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (++i < len && start < ft_strlen(str))
		s[i] = str[start++];
	s[i] = '\0';
	return (s);
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
