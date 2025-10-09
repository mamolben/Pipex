#include "pipex.h"

// Cuenta cuántas "substrings" hay según el delimitador.
size_t	count_substr(const char *s, char c)
{
	size_t	count = 0;
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

// Libera la memoria del array parcial en caso de fallo de malloc.
void	free_split(char **array, size_t idx)
{
	while (idx > 0)
		free(array[--idx]);
	free(array);
}

// Copia la substring con ayuda de ft_substr (de libft).
char	*copy_substr(const char *start, char c)
{
	size_t	len = 0;
	while (start[len] && start[len] != c)
		len++;
	return (ft_substr(start, 0, len)); // Usando libft para modularidad.
}

// Llena el array principal llamando a la copia por substring.
int	fill_array(char **array, const char *s, char c, size_t count)
{
	size_t	i = 0;
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

// La función principal ft_split con delegación clara.
char	**ft_split(char const *s, char c)
{
	char		**array;
	size_t		count;

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
