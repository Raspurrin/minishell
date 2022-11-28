/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:47:59 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/28 20:59:13 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

/**
 * @brief finds the first quote type in name.
 * 
 * @param name the string in which we are looking for quote
 * @return char, the type of quote that is first seen. 
 */

char	quote_type(char *name)
{
	if (!ft_strchr(name, '\'') && !ft_strchr(name, '\"'))
		return (0);
	if (pos_char_start(name, '\"') < pos_char_start(name, '\''))
		return ('\"');
	return ('\'');
}

/**
 * @brief removes the oppening and closing quotes.
 * 
 * @param name the string
 * @param start is the place of starting quote.
 * @return char* the string with removed strings.
 */

char	*rm_two_quotes(char *name, int start)
{
	int		i;
	int		j;
	int		end;
	char	*result;

	i = 0;
	j = 0;
	end = start + skip_quotes(name + start) - 1;
	result = ft_calloc(sizeof(char), ft_strlen(name) - 1);
	while (name[i])
	{
		if (i != start && i != end)
		{
			result[j] = name[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free (name);
	return (result);
}

/**
 * @brief removes all the necessary quotes.
 * skips the quotes that are inside another quote.
 * 
 * @param name the string
 * @return char* the result string which is free of all the first coming quotes
 * (the inside quotes should not be removed.) 
 */

char	*rm_quotes_all(char *name)
{
	int	i;
	int	tmp;

	i = 0;
	while (name[i])
	{
		if (name[i] == '\"' || name[i] == '\'')
		{
			tmp = i;
			i += skip_quotes(name + i) - 3;
			name = rm_two_quotes(name, tmp);
		}
		i++;
	}
	return (name);
}
