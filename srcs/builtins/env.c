/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 01:52:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 04:47:58 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_data *data, t_group *group)
{
	t_env	*lst;

	(void)group;
	lst = data->envp_head;
	while (lst->next != NULL)
	{
		printf("keyvalue: %s\n", lst->keyvalue);
		lst = lst->next;
	}
}
