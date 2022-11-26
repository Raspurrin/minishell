/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:10:22 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/11/26 16:48:17 by pmoghadd         ###   ########.fr       */
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

void	*ft_memalloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!(ret))
		return (NULL);
	ft_bzero(ret, size);
	return (ret);
}

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	*ft_realloc2(void *src, size_t old_len, size_t new_len)
{
	void	*res;

	res = ft_memalloc(new_len);
	if (!(res))
		return (NULL);
	ft_memcpy(res, src, old_len);
	ft_memdel(&src);
	return (res);
}
