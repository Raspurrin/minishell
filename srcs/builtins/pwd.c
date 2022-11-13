/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/13 05:03:42 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pwd(t_data *data)
{
	t_env	*lst;

	lst = find_node(data->envp_head, "PWD");
	if (lst)
		data->pwd = ft_strdup(lst->value);
	else
		data->pwd = NULL;
	ft_printf_fd(STDERR_FILENO, "yo: %s", data->pwd);
}

void	pwd(t_data *data, t_group *group)
{
	(void)group;

	ft_printf_fd(STDERR_FILENO, "lst->value from pwd: %s\n", data->pwd);
	ft_printf_fd(STDOUT_FILENO, "%s\n", data->pwd);
}
