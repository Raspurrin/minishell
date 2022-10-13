/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:04:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/13 18:07:21 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(t_data *data, t_group *group)
{
	bool	option;
	size_t	i;

	i = 1;
	(void)data;
	option = false;
	if (group->full_cmd[1])
	{
		if (ft_strncmp("-n", (group->full_cmd[1]), 2))
			option = true;
	}
	while ((group->full_cmd[i]))
		printf("%s", group->full_cmd[i++]);
	if (option)
		printf("\n");
}
