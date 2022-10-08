/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 03:29:46 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_data *data)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst->next != NULL)
	{
		if (ft_strncmp("PWD", lst->key, 3))
			return (lst->key);
		lst = lst->next;
	}
}

static void	pwd(t_data *data, t_group *group)
{
	printf("%s", lst->value);
}
