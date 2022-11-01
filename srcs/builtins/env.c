/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:52:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/01 02:27:40 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_data *data, t_group *group)
{
	t_env	*lst;

	(void)group;
	ft_printf_fd(STDERR_FILENO, "hi\n");
	lst = data->envp_head;
	while (lst != NULL)
	{
		if (lst->value)
			printf("%s\n", lst->keyvalue);
		lst = lst->next;
	}
}
