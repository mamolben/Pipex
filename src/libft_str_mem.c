#include "pipex.h"

size_t ft_strlen(const char *str)
{
    size_t len = 0;

    while (str && str[len])
        len++;
    return (len);
}

char *ft_strdup(const char *str)
{
    char *dup;
    size_t len = ft_strlen(str);
    size_t pos = 0;

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

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *substr;
    size_t i;

    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    if (len > ft_strlen(s + start))
        len = ft_strlen(s + start);
    substr = malloc(len + 1);
    if (!substr)
        return (NULL);
    i = 0;
    while (i < len)
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return (substr);
}

void ft_free(char **str)
{
    int pos = 0;
    if (!str)
        return;
    while (str[pos])
    {
        free(str[pos]);
        pos++;
    }
    free(str);
}
