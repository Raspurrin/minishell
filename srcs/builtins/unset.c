/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:21 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/21 02:33:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Unsetting env node. Whenever the right node has been found, 
 * set the next pointer of the previous node to the following node: 
 * [prev]->[cur]->[next]	->		[prev]->[next]
 * Or if node is the head, just make the next node the start of the list.
 */
bool	unset(t_data *data, t_group *group)
{
	size_t	i;
	t_env	*lst;
	t_env	*prev;

	i = 1;
	if (!group->full_cmd[i])
		return (false);

	while (group->full_cmd[i])
	{
		while (!check_key(group->full_cmd[i])) // no u
		{
			ft_printf_fd(STDERR_FILENO, "check_export failed\n");
			if (!group->full_cmd[i + 1])
				return (display_error(data, INVID, false, \
							join_err(group->full_cmd[i], "")), false);
			i++;
		}
		lst = data->envp_head;
		prev = lst;
		while (lst != NULL)
		{
			if (ft_strcmp(group->full_cmd[i], lst->key) == 0)
			{
				if (lst == data->envp_head && lst->next)
					data->envp_head = lst->next;
				else if (lst->next)
					prev->next = lst->next;
				free_env_node(lst, 1);
				if (lst->next == NULL)
					prev->next = NULL;
				break ;
			}
			prev = lst;
			lst = lst->next;
		}
		i++;
	}
	return (true);
}
