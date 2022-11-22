/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:10:22 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/22 21:50:42 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_array(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/**
 * @brief the first char of variable in bash can be either low or upper
 * case chars or '_'. number is not accepted.
 * @param c 
 * @return int 
 */

int	first_char_check(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	return (0);
}

int	err_parser(char *msg, char c)
{
	printf("%s '%c'\n", msg, c);
	return (-1);
}
