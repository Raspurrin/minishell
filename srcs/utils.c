/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:06:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/07 01:39:36 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_2darr(t_data *data, t_env *lst)
{
	char	**env;
	size_t	i;

	i = 0;
	env = malloc(data->envpc * sizeof(char *));
	while (lst->next != NULL)
	{
		env[i++] = lst->keyvalue;
		// printf("%s\n", env[0]);
		lst = lst->next;
		// env[1] = lst->keyvalue;
		// printf("%s", env[1]);
	}
	return (env);
}
