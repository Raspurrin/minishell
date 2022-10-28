/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:52:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/28 15:09:07 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_data *data, t_group *group)
{
	t_env	*lst;

	(void)group;
	lst = data->envp_head;
	printf("%p\n", data->envp_head);
	printf("%p\n", data->envp_head->next);
	while (lst != NULL)
	{
		if (lst->value)
			printf("%s\n", lst->keyvalue);
		lst = lst->next;
	}
}
