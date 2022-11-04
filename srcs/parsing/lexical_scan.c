/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:24:43 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/03 22:40:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_chars(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = i + skip_quotes(s + i) - 1;
		i++;
	}
	return (i);
}

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

int	special_chars(t_data *data, t_group **info, char *s)
{
	int i;
	int	space;
	int	end = 0;
	int	indicator;
	// int	word_counter = 0;

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
		in_file_init(data, info, s, ft_substr(s, space + 1 + indicator, end));
	else if (s[0] == '>')
		out_file_init(data, info, s, ft_substr(s, space + 1 + indicator, end));
	else
		words_init(data, info, ft_substr(s, space + 1 + indicator, end));
	// while ((*info)->outfile->next != NULL)
	// {
	// 	printf("the good the abd the ugly%s\n", (*info)->outfile->name);
	// 	(*info)->outfile = (*info)->outfile->next;
	// }
	return (end + space + indicator);
}

int	quoted_word_extract(t_data *data, t_group **info, char *s)
{
	// int	i;
	int	end;
	// int	space;

	end = skip_quotes(s);
	words_init(data, info, ft_substr(s, 0, end));
	return (end);
}

int	normal_word_extract(t_data *data, t_group **info, char *s)
{
	int	end;
	int	i;

	i = 0;
	end = skip_chars(s);
	// while (s[i] && s[i] != ' ')
	// {
	// 	if (s[i] == '"')
	// 	{
	// 		i = skip_quotes(s);
	// 		end = i; 
	// 		if (s[i] && s[i + 1] == ' ')
	// 			break;
	// 	}
	// 	i++;
	// }
	// end = i;
	words_init(data, info, ft_substr(s, 0, end));
	return (end);
}
