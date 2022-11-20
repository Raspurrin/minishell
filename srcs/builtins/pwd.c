/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 03:45:23 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Cheeeeeeeeeeeeeese.
 */
bool	pwd(t_data *data, t_group *group)
{
	size_t	size;
	size_t	old_size;
	char	*buf;

	(void)group;
	(void)data;
	size = 100;
	buf = malloc(size);
	if (!buf)
		return (false);
	while (true)
	{
		buf = getcwd(buf, size);
		if (buf)
			break ;
		old_size = size;
		size += 100;
		buf = ft_realloc_n(buf, size, old_size);
		if (!buf)
			return (false);
	}
	ft_printf_fd(STDOUT_FILENO, "%s\n", buf);
	return (free (buf), true);
}
