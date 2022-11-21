/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:47:59 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/21 13:48:27 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	quote_type(char *name) //finds the first quote in name
{
	if (!ft_strchr(name, '\'') && !ft_strchr(name, '\"'))
		return (0);
	if (pos_char_start(name, '\"') < pos_char_start(name, '\''))
		return ('\"');
	return ('\'');
}

char *remove_quotes(char *name, int start)
{
	int	i;
    int end;
	char *result;
    int j;

	i = 0;
    j = 0;
    end = start + skip_quotes(name + start) - 1;
	result = ft_realloc(name, sizeof(char) * (ft_strlen(name) - 1));
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

char * rm_quotes_(char *name)
{
	int i;
	int tmp;

	i = 0;
	while (name[i])
	{
		if (name[i] == '\"' || name[i] == '\'')
		{
			tmp = i;
			i += skip_quotes(name + i) - 3;
			name = remove_quotes(name, tmp);
		}
		i++;
	}
	return (name);
}
