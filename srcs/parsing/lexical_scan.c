/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:24:43 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/26 17:23:47 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief as clear it is, it skips chars other than space!
 * if sees quote, skips!
 * @param s 
 * @return int the place which is either end or space in the string
 */
int	skip_chars(char *s)
{
	int	i;
	int	end;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = i + skip_quotes(s + i) - 1;
		if ((s[i] == '>' || s[i] == '<') && (i != 0 && i != 1))
			break ;
		i++;
	}
	end = i;
	return (end);
}

/**
 * @brief skips stuff inside a quote
 * 
 * @param s string with a begging char of quote
 * @return int the place of after quote char index
 */

int	skip_quotes(char *s)
{
	char	quote_type;
	int		i;

	i = 1;
	quote_type = s[0];
	while (s[i] && s[i] != quote_type)
		i++;
	return (i + 1);
}

/**
 * @brief if a special char is found, is handed to this function.
 * this finds out which redirection type (in, heredoc, out, append) 
 * it is and passes to the suitable func
 * 
 * @param info the data struchture of each data group. 
 * @param s the string we are talking abt
 * @param envp env pointer is saved here
 * @return int number of chars that are read. 
 */

int	special_chars(t_group **info, char *s, t_env *envp)
{
	int	i;
	int	space;
	int	end;
	int	indicator;

	end = 0;
	indicator = 0;
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		indicator = 1;
	space = skip_spaces(s + 1 + indicator);
	i = space + indicator + 1;
	if (s[i] == '\'' || s[i] == '"')
			end = skip_quotes(s + i);
	else
			end = skip_chars(s + i);
	if (s[0] == '<')
		in_file_init(info, s, ft_substr(s, space + 1 + indicator, end), envp);
	else if (s[0] == '>')
		out_file_init(info, s, ft_substr(s, space + 1 + indicator, end), envp);
	else
		words_init(info, ft_substr(s, space + 1 + indicator, end), envp);
	return (end + space + indicator);
}

int	quoted_word_extract(t_group **info, char *s, t_env *envp)
{
	int	end;

	end = skip_quotes(s);
	if (*(s + end) && ((*(s + end) != ' '\
		&& *(s + end) != '<' && *(s + end) != '>')))
		end = end + skip_chars(s + end);
	words_init(info, ft_substr(s, 0, end), envp);
	return (end - 1);
}

int	normal_word_extract(t_group **info, char *s, t_env *envp)
{
	int	end;
	int	i;

	i = 0;
	end = skip_chars(s);
	words_init(info, ft_substr(s, 0, end), envp);
	return (end - 1);
}
