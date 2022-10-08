/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:21 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 04:50:09 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_data *data, t_group *group)
{
	t_env	*lst;
	t_env	*prev;

	lst = data->envp_head;
	prev = lst;
	while (lst->next != NULL)
	{
		if (ft_strncmp(group->full_cmd[1], lst->key, ft_strlen(lst->key)) == 0)
		{
			if (lst == data->envp_head)
				lst->next = data->envp_head;
			else
				prev->next = lst->next;
			break ;
		}
		prev = lst;
		lst = lst->next;
	}
}
