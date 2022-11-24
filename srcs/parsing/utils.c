/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:54:11 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/24 14:19:16 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

/**
 * @brief this is for freeing, because i am passing an allocated 
 * memory and i need this to free that string.
 * the only diff with strjoin is this.
 * @param str1 the string i am talking abt
 * @param str2 
 * @return char* 
 */
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
	free(str1);
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

/**
 * @brief this is also like isalnum. 
 * the diff is that in shell the '_' character is allowed to be part of variable.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool	ft_isalnum_ms(int32_t c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || \
	(c >= 'A' && c <= 'Z') || (c == '_'))
		return (true);
	return (false);
}
