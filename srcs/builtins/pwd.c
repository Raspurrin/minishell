/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/09 20:33:10 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pwd(t_data *data)
{
	t_env	*lst;

	lst = find_node(data->envp_head, "PWD");
	if (lst->value)
		data->pwd = ft_strdup(lst->value);
	else
		data->pwd = NULL;
	ft_printf_fd(STDERR_FILENO, "yo: %s", data->pwd);
}

void	pwd(t_data *data, t_group *group)
{
	(void)group;
	if (!data->pwd)
		init_pwd(data);
	printf("%s\n", data->pwd);
}
