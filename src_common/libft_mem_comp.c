/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:01:25 by marimoli          #+#    #+#             */
/*   Updated: 2025/11/23 18:33:36 by marimoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ====== Libera un array de strings ======*/
void	ft_free(char **str)
{
	int	pos;

	pos = 0;
	if (!str)
		return ;
	while (str[pos])
	{
		free(str[pos]);
		pos++;
	}
	free(str);
}

/* ====== Compara los n caracteres de dos cadenas ======*/
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	pos;

	pos = 0;
	while (pos < n && (str1[pos] || str2[pos]))
	{
		if (str1[pos] != str2[pos])
			return ((unsigned char)str1[pos] - (unsigned char)str2[pos]);
		pos++;
	}
	return (0);
}
