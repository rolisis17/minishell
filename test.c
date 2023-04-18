#include <stdio.h>
#include "./libft/libft.h"
#include "minishell.h"

void	freesplit(char **splited);

int	word_count(char const *str, char c)
{
	int	words;
	int	len;

	words = 0;
	while (*str != '\0')
	{
		while (*str == c && *str != '\0')
			str++;
		if (*str != '\0')
			words++;
		len = 0;
		while (str[len] != c && str[len] != '\0')
			len++;
		str += len;
	}
	return (words);
}

int main()
{
    char *str = "'stringwith'moreshit";
    char *start;
    char *end;
    int     len;
    // char **split;
    // int i = 0;

	// split = (char **) malloc(sizeof(char *) * (word_count(str, 39) + 1));
    // printf("%s\n", str);
    // while(1)
    // {    
    //     start = ft_strchr(str, 39);
    //     if (start != NULL)
    end = ft_strchr(str + 1, 39);
    //     if (start == NULL || end == NULL)
    //     {
    //         split[i++] = ft_substr(str, 0, ft_strlen(str));
    //         break;
    //     }
    //     else if (str[0] != 39 && end != NULL)
    //     {
    start = ft_substr(str, 1, end - str - 1); // maybe -1
    //         str = start;
    //     }
    //     else
    //     {
    //         split[i++] = ft_substr(str, 0, end - start + 1);
    //         str = end + 1;
    //     }
    // }
    // split[i] = NULL;
    // i = 0;
    // while (split[i])
    len = ft_strlen()
    printf("%s\n", start);
    free(start);
}

void	freesplit(char **splited)
{
	int	counter;

	counter = 0;
	while (splited[counter])
	{
		free(splited[counter]);
		counter++;
	}
	free (splited);
}

