#include "pipex.h"

static int count_words(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return (count);
}

static char *word_dup(const char *s, int start, int end)
{
    int len = end - start;
    char *word = malloc(len + 1);
    int i = 0;

    if (!word)
        return (NULL);
    while (start < end)
    {
        word[i++] = s[start++];
    }
    word[i] = '\0';
    return (word);
}

char **ft_split(const char *str, char car)
{
    char    **result;
    int     i = 0;
    int     j = 0;
    int     start = -1;

    if (!str)
        return (NULL);
    result = malloc((count_words(str, car) + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while (str[i])
    {
        if (str[i] != car && start < 0)
            start = i;
        else if ((str[i] == car || str[i + 1] == '\0') && start >= 0)
        {
            result[j++] = word_dup(str, start, i + (str[i] != car));
            start = -1;
        }
        i++;
    }
    result[j] = NULL;
    return (result);
}
