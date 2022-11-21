/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:54:20 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 18:13:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	exit_check(t_data *data, t_group *group)
{
	size_t	i;
	int32_t	nbr;

	i = 0;
	nbr = 0;
	(void)data;
	if (ft_strncmp(group->full_cmd[0], "exit", 4) == 0)
	{
		if (group->full_cmd[1])
		{
			while (ft_isdigit(group->full_cmd[1][i]))
				i++;
			if (group->full_cmd[1][i] && !ft_isdigit(group->full_cmd[1][i]))
				return (/*display_error(data, "", false),*/ false);
			nbr = ft_atoi(group->full_cmd[1]);
		}
		printf("exit\n");
		exit(nbr);
	}
	return (true);
}
