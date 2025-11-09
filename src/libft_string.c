/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:47:48 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/07 18:14:36 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;
	size_t	pos;

	len = ft_strlen(str);
	pos = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (pos < len)
	{
		dup[pos] = str[pos];
		pos++;
	}
	dup[pos] = '\0';
	return (dup);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	pos;

	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	if (len > ft_strlen(str + start))
		len = ft_strlen(str + start);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	pos = 0;
	while (pos < len)
	{
		substr[pos] = str[start + pos];
		pos++;
	}
	substr[pos] = '\0';
	return (substr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resul;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	resul = malloc(len1 + len2 + 1);
	if (!resul)
		return (NULL);
	ft_strlcpy(resul, s1, len1 + 1);
	ft_strlcpy(resul + len1, s2, len2 + 1);
	return (resul);
}
