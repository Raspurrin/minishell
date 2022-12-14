/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:36:03 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/28 20:13:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief the split is amended in a way that it wont consider invalid pipes as a 
 * pipe and will split only by valid pipes.
 * the subfunctions are splits subfuns. 
 * @param s ...
 * @param c ...
 * @return ...
 */

static size_t	ft_count_words(const char *s, char c)
{
	size_t		number_of_pipes;
	size_t		i;
	size_t		mark;

	mark = 0;
	number_of_pipes = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = i + skip_quotes((char *)s + i) - 1;
		if (s[i] == c && mark == 0)
		{
			mark = 1;
			number_of_pipes++;
		}
		if (s[i] != c)
			mark = 0;
		i++;
	}
	return (number_of_pipes + 1);
}

static size_t	ft_word_len_shell(const char *s, char c, size_t i)
{
	size_t	nbr_of_letters;

	nbr_of_letters = 0;
	while (i < ft_strlen(s) && s[i] != c)
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			nbr_of_letters += skip_quotes((char *)s + i) - 1;
			i += skip_quotes((char *)s + i) - 1;
		}
		nbr_of_letters++;
		i++;
	}
	return (nbr_of_letters);
}

char	**ft_split_shell(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**lst;

	if (s == 0)
		return (0);
	i = 0;
	j = 0;
	lst = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!lst)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		lst[i] = (char *)malloc(sizeof(char)
				* (ft_word_len_shell(s, c, j) + 1));
		if (!lst[i])
			free (lst[i]);
		ft_strlcpy(lst[i], &s[j], ft_word_len_shell(s, c, j) + 1);
		j = j + ft_word_len_shell(s, c, j);
		i++;
	}
	lst[i] = 0;
	return (lst);
}
