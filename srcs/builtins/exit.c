/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:54:20 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 23:29:52 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int8_t	exit_check(t_data *data, t_group *group)
{
	size_t	i;
	int32_t	nbr;
	bool	errno;

	i = 0;
	nbr = 0;
	errno = false;
	(void)data;
	if (group->full_cmd[2])
	{
		printf("exit\n");
		g_exitcode = 1;
		return (display_error(ARGS, join_err(NULL, NULL), NULL, group), 1);
	}
	else if (ft_strncmp(group->full_cmd[0], "exit", 4) == 0)
	{
		if (group->full_cmd[1])
		{
			while (ft_isdigit(group->full_cmd[1][i]))
				i++;
			if (group->full_cmd[1][i] && !ft_isdigit(group->full_cmd[1][i]))
				errno = true;
			nbr = ft_atoi(group->full_cmd[1]);
		}
		printf("exit\n");
		if (errno)
			display_error(ARGS, join_err(NULL, NULL), NULL, group);
		shlvl_msg(data->envp_head, true);
		free_data(data);
		exit(nbr);
	}
	return (0);
}
