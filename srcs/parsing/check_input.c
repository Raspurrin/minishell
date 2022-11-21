/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:58:33 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/21 13:50:48 by pmoghadd         ###   ########.fr       */
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
	while (s[i] && (s[i] == c || (s[i] == '>' || s[i] == '<' || s[i] == ')' || s[i] == '(')))
	{
		i++;
		a++;
		if (s[i] && (s[i] == ' '))
			i += skip_spaces(s + i);
	}
	if (a >= 3)
		return (-1);
	else if(a >= 2 && (s[0] != s[1] || ft_strchr("&;()", c)))
		return (-1);
	return (i - 1);
}

int skip_spaces_backwards(char *s, int i)
{
	int j;

	j = i - 1;
	while (s[j] && j >= 0 && s[j] == ' ')
		j--;
	return (j);	
}

int pipe_check(char *s)
{
	int	i;
	// int	pipe_place;
	
	i = ft_strlen(s) - 1;
	if (s[0] == '|' || (s[skip_spaces(s)] && s[skip_spaces(s)] == '|')) //starts with a pipe
		return (-1);
	while (i >= 0 && s[i] != '|' && s[i] == ' ' ) //ends with a pipe
		i--;
	if (s[i] == '|')
		return (-1);
	i = 0;
	while (s[i]) //special cases
	{
		if ( s[i] == '|')
		{
			if (s[skip_spaces_backwards(s, i)] == '<' ||  s[skip_spaces_backwards(s, i)] == '>')
				return (-1);
		}
		i++;
	}
	return (0);
}

int space_check(char *s)
{
	char *tmp;

	tmp = ft_strtrim(s, " ");
	if(ft_strlen(tmp) == 0)
		{
			free(tmp);
			return (0);
		}
	return (1);
}

int		check_input_before_handling(char *s)
{
	int	i;

	i = 0;
	if(pipe_check(s) != 0)
		return (err_parser("Minishell: syntax error near unexpected token", '|'));
	if (s[0] == '|' || (s[skip_spaces(s)] && s[skip_spaces(s)] == '|'))
		return (err_parser("Minishell: syntax error near unexpected token", '|'));
	if (!space_check(s) || (ft_strlen(s) == 1 && s[0] != '-' && s[0] != '/'))
		return (1);
	// if (s[skip_spaces(s)] == s[skip_spaces(s) + 1] && (s[1] == '>' || s[1] == '<'))
	// 	 return (err_parser("Minishell: syntax error near unexpected token 'newline'", 0));
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!s[i + skip_quotes(s + i) - 1])
				return (err_parser("Minishell: error, unclosed quote", s[i]));
			i += skip_quotes(s + i) - 1;
		}
		if (ft_strchr("><&;()", s[i]))
		{
			if (check_neighbouring_chars(s + i) == -1)
				return (err_parser("Minishell: synax error near unexpected token", s[i]));
			i = i + check_neighbouring_chars(s + i);
		}
		i++;
	}
	return (0);
}
