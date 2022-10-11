/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 19:09:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * It seems like the environmental variable PWD doesn't change its value 
 * after using chdir(), which is why I am manually changing this string.
*/
void	cd(t_data *data, t_group *group)
{
	size_t	i;
	size_t	len;

	i = 0;
	chdir(group->full_cmd[1]);
	if (ft_strncmp(group->full_cmd[1], "../", 3) == 0)
	{
		len = ft_strlen(data->pwd);
		while (data->pwd[len] != '/')
			len--;
		printf("len: %zu\n", len);
		if (len == 0)
			data->pwd = "/";
		else
			data->pwd = ft_substr(data->pwd, 0, len);
	}
	else
	{
		data->pwd = ft_strjoin(data->pwd, "/");
		data->pwd = ft_strjoin(data->pwd, group->full_cmd[1]);
	}
}
