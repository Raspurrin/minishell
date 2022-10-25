/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:09:10 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/13 17:45:37 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	m_howmany(char const *s, char c)
// {
// 	int	amount;
// 	int	i;

// 	if (!s)
// 		return (0);
// 	amount = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			amount++;
// 		i++;
// 	}
// 	return (amount);
// }

// void	*m_ft_free(char **arr, int j)
// {
// 	int	i;

// 	i = 0;
// 	while (i < j)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (NULL);
// }

int m_how_many(const char *s, char c, char q)
{
    int i;
    int amount;

    i = 0;
    amount = 0;
    while (s[i])
    {
        if ((s[i] == c || s[i] == q) && (s[i + 1] && s[i + 1] != c && s[i + 1] != q))
            amount++;
        i++;
    }
    return (amount);
}

int	m_skip_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ( s[i] == ' ' || s[i] == '\t'
		|| s[i] == '\n')) //add all the white spaces
		i++;
	return (i);
}

char    **minishell_split(const char *s, char c, char q)
{
    int i;
    int j = 0;
    int k;
    int start = 0;
    char **res;

    i = 0;
    k = i;
    res = (char **)malloc(sizeof(char *) * m_how_many(s, c, q)); //later to be amended
    if (!res)
        return (NULL);
    while (s[i])
    {
        while (s[k] && (s[k] != c && s[k] != q))
            k++;
        if (s[k] == q)
        {
            start = k;
            k++;
            while (s[k] && s[k] != q)
                k++;
             res[j] = ft_substr(s, start, k - start + 1);
             k++;
        }
        else
            res[j] = ft_substr(s, i + m_skip_spaces(s + i), k - i - m_skip_spaces(s + i));  
        j++;
        i = k;
        k++;
    }
    res[j] = NULL;
    return (res);
}
// int main()
// {
//     char *s="hello \"this is a unit\" and I want to split \"this together\"  \"    h   \"  ff "" hi hello my";
//     char **res = minishell_split((const char *)s, ' ', '\"');
//     printf("out: %s\n", res[6]);
// }