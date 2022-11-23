/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:58:33 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/23 14:47:47 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

static bool	pipe_check(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (s[0] == '|' || (s[skip_spaces(s)] && s[skip_spaces(s)] == '|')) //starts with a pipe
		return (true);
	while (i >= 0 && s[i] != '|' && s[i] == ' ' ) //ends with a pipe
		i--;
	if (s[i] == '|')
		return (true);
	i = 0;
	while (s[i]) //special cases
	{
		if (s[i] == '|')
		{
			if (s[skip_spaces_backwards(s, i)] == '<'
				||s[skip_spaces_backwards(s, i)] == '>')
				return (true);
		}
		i++;
	}
	return (false);
}

static bool	space_check(char *s)
{
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	if (ft_strlen(tmp) == 0
		|| (ft_strlen(tmp) == 1 && (tmp[0] == ':'
				|| tmp[0] == '!')))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

static bool	only_one_char(char *s)
{
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	if (ft_strlen(tmp) == 1 && s[0] != '-' && s[0] != '/'
		&& s[0] != ':' && s[0] != '!' && s[0] != '*'
		&& s[0] != '.' && s[0] != '~')
		return (free(tmp), true);
	else if (ft_strlen(tmp) == 2 && (ft_strchr("<>", tmp[0])
			|| ft_strchr("<>", tmp[1]))) //<< and >> and <>
		return (free(tmp), true);
	free(tmp);
	return (false);
}

bool	check_input_before_parsing_helper(char *s)
{
	if (pipe_check(s))
		return (display_error(TOKEN, join_err(NULL, " '|' "), NULL, NULL), true);
	if (!space_check(s))
		return (1);
	if (only_one_char(s))
		return (display_error(TOKEN, join_err(NULL, "\'newline\'"), NULL, NULL), true);
	return (false);
}

int	check_input_before_parsing(char *s)
{
	int		i;
	char	c;

	i = 0;
	if(pipe_check(s))
		return (display_error(TOKEN, join_err(NULL, NULL), NULL, NULL), 1);
	if (!space_check(s))
		return (1);
	if (only_one_char(s))
		return (display_error(TOKEN, join_err(NULL, "\'newline\'"), NULL, NULL), 1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!s[i + skip_quotes(s + i) - 1])
				return (c = s[i], ft_perror(&c, false), 1); //seg faults , shoould fix this
			i += skip_quotes(s + i) - 1;
		}
		if (ft_strchr("><&;()", s[i]))
		{
			if (check_neighbouring_chars(s + i) == -1)
				return (c = s[i], display_error(TOKEN, join_err(NULL, &c), NULL, NULL), 1);
			i = i + check_neighbouring_chars(s + i);
		}
		i++;
	}
	return (0);
}
