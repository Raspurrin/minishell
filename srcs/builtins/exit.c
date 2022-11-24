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

uint32_t	exit_check(t_data *data, t_group *group)
{
	size_t	i;
	size_t	len;
	uint32_t	nbr;
	bool	errno;

	i = 0;
	nbr = 0;
	errno = false;
	(void)data;
	if (group->full_cmd[2] && !group->full_cmd[3])
	{
		printf("exit\n");	g_exitcode = 1;
		fprintf(stderr, "group->full_cmd[2]: %s group->full_cmd[3]: %s\n", group->full_cmd[2], group->full_cmd[3]);
		return (display_error(ARGS, join_err(NULL, NULL), NULL, group), 1);
	}
	if (group->full_cmd[1])
	{
		len = ft_strlen(group->full_cmd[1]);
		if (len > 10 && ft_strncmp(group->full_cmd[1], ft_itoa(INT_MAX), len))
			return(ft_atoi(group->full_cmd[1]));
		while (ft_isdigit(group->full_cmd[1][i]))
			i++;
		if (group->full_cmd[1][i] && !ft_isdigit(group->full_cmd[1][i]))
			errno = true;
		nbr = ft_atoi(group->full_cmd[1]);
	}
	printf("exit\n");
	fprintf(stderr, "brrrrrrr | exitcode: %d\n", nbr);
	ft_printf_fd(STDERR_FILENO, "data->envp_head: %p\n", data->envp_head);
	// print_env(data->envp_head);
	t_env *env = find_node(data->envp_head, "SHLVL");
	ft_printf_fd(STDERR_FILENO, "SHLVL node: %p\n", env);
	shlvl_msg(data->envp_head, true);
	if (errno)
		display_error(NUMARG, join_err(NULL, NULL), NULL, group);
	// free_data(data);
	g_exitcode = nbr;
	exit(nbr);
	return (nbr);
}
