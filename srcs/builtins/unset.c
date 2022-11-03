/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:21 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/02 18:26:01 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*lst;
	t_env	*prev;

	i = 0;
	while (group->full_cmd[i])
	{
		lst = data->envp_head;
		prev = lst;
		while (lst->next != NULL)
		{
			if (ft_strncmp(group->full_cmd[i], lst->key, \
									ft_strlen(lst->key)) == 0)
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
		i++;
	}
	lst->next = NULL;
}
