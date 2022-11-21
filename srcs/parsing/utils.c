/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:54:11 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/21 13:52:38 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

// void	print_linkedlist(t_token *data)
// {
// 	t_token	*tmp;
// 	size_t	i;

// 	tmp = data;
// 	i = 0;
// 	while (tmp->next != NULL)
// 	{
// 		printf("i: %zu   element:%s\n", i, tmp->infile->name[0]);
// 		tmp = tmp->next;
// 	}
// }
char	*ft_strjoin_minishell(char *str1, char *str2)
{
	size_t	str1len;
	size_t	str2len;
	char	*out;

	if (!str1 || !str2)
		return (0);
	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	out = ft_calloc((str1len + str2len + 1), sizeof(char));
	if (!out)
		return (0);
	ft_strlcpy(out, str1, str1len + 1);
	ft_strlcpy(out + str1len, str2, str2len + 1);
	// free(str1);
	return (out);
}

void	lstaddback(t_infile **lst, t_infile *new)
{
	t_infile	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new;
	else
	{	
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lstaddback_out(t_outfile **lst, t_outfile *new)
{
	t_outfile	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{	
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'
			|| s[i] == '\n'))
		i++;
	return (i);
}

bool	ft_isalnum_ms(int32_t c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || (c == '_'))
		return (true);
	return (false);
}

int	first_char_check(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	return (0);
}

int err_parser(char *msg, char c)
{
    printf("%s '%c'\n", msg, c);
    return (-1);
    // exit(EXIT_FAILURE);
}