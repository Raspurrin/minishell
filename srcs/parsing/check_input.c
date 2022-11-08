/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:58:33 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/01 11:36:38 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int	check_neighbouring_chars(char *s)
{
	char c;
	int	i;

	c = s[0];
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (c == '|' && i >= 2)
	{
		printf("Minishell: syntax error near unexpected token `%c'\n",c); //add err file
		exit(45);
	}
	else if (i >= 3)
	{
		printf("Minishell: syntax error near unexpected token `%c'\n",c); //add err file
		exit(45);//what here ?
	}
	return (i);
}

void		check_input_before_handling(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!s[i + skip_quotes(s + i) - 1]) //add error function and exit code
			{
				printf("Minishell: unclosed quote!\n");
				exit(45);
			}
			i += skip_quotes(s + i);
		}
		if (ft_strchr("><|", s[i]))
		{
			i = i + check_neighbouring_chars(s + i);
		}
		i++;
	}
}