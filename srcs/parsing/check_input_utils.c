/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:23:10 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/22 20:34:52 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int	check_neighbouring_chars(char *s)
{
	char	c;
	int		i;
	int		a;

	c = s[0];
	i = 0;
	a = i;
	while (s[i] && (s[i] == c || (s[i] == '>' || s[i] == '<'
				|| s[i] == ')' || s[i] == '(')))
	{
		i++;
		a++;
		if (s[i] && (s[i] == ' '))
			i += skip_spaces(s + i);
	}
	if (a >= 3)
		return (-1);
	else if (a >= 2 && (s[0] != s[1] || ft_strchr("&;()", c)))
		return (-1);
	return (i - 1);
}

int	skip_spaces_backwards(char *s, int i)
{
	int	j;

	j = i - 1;
	while (s[j] && j >= 0 && s[j] == ' ')
		j--;
	return (j);
}
