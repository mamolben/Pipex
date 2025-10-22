/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:53:26 by marimoli          #+#    #+#             */
/*   Updated: 2025/10/19 12:44:53 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	count_substr(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

void	free_split(char **array, size_t idx)
{
	while (idx > 0)
		free(array[--idx]);
	free(array);
}

char	*copy_substr(const char *start, char c)
{
	size_t	len;

	len = 0;
	while (start[len] && start[len] != c)
		len++;
	return (ft_substr(start, 0, len));
}

int	fill_array(char **array, const char *s, char c, size_t count)
{
	size_t	i;

	i = 0;
	while (*s && i < count)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			array[i] = copy_substr(s, c);
			if (!array[i])
			{
				free_split(array, i);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	array[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_substr(s, c);
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	if (!fill_array(array, s, c, count))
	{
		free(array);
		return (NULL);
	}
	return (array);
}
