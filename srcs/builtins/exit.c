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

bool	check_digits(t_group *group)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(group->full_cmd[1]);
	if (len > 10 && ft_strncmp(group->full_cmd[1], ft_itoa(INT_MAX), len))
		return (ft_atoi(group->full_cmd[1]));
	while (ft_isdigit(group->full_cmd[1][i]))
		i++;
	if (group->full_cmd[1][i] && !ft_isdigit(group->full_cmd[1][i]))
		return (false);
	return (true);
}

uint32_t	exit_check(t_data *data, t_group *group)
{
	uint32_t	nbr;
	bool		digits;

	nbr = 0;
	digits = true;
	(void)data;
	if (group->full_cmd[1] && group->full_cmd[2])
	{
		printf("exit\n");
		g_exitcode = 1;
		return (display_error(ARGS, join_err(NULL, NULL), NULL, group), 1);
	}
	if (group->full_cmd[1])
	{
		digits = check_digits(group);
		nbr = ft_atoi(group->full_cmd[1]);
	}
	printf("exit\n");
	shlvl_msg(data->envp_head, true);
	if (!digits)
		display_error(NUMARG, join_err(NULL, NULL), NULL, group);
	g_exitcode = nbr;
	exit(nbr);
	return (nbr);
}
