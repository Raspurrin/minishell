/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:21 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/12 01:01:21 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Unsetting env node. Whenever the right node has been found, 
 * set the next pointer of the previous node to the following node: 
 * [prev]->[cur]->[next]	->		[prev]->[next]
 * Or if node is the head, just make the next node the start of the list.
 */
void	unset(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*lst;
	t_env	*prev;

	i = 1;
	
	while (group->full_cmd[i])
	{
		lst = data->envp_head;
		prev = lst;
		while (lst->next != NULL)
		{
			if (ft_strncmp(group->full_cmd[i], lst->key, ft_strlen(lst->key)) == 0 \
			&& !ft_strncmp(group->full_cmd[i], lst->key, ft_strlen(group->full_cmd[i])))
			{
				if (lst == data->envp_head)
					lst->next = data->envp_head;
				else
					prev->next = lst->next;
				free_env_node(lst, true);
				break ;
			}
			prev = lst;
			lst = lst->next;
		}
		i++;
	}
}
