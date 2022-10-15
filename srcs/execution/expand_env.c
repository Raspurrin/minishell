/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:10:33 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/14 18:26:26 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// hallo $ENV sup $ENV2
// lenght of str - length of env variables + length of env values
// hallo Anahit sup Pooneh

t_env	*cmp_lst(char *str, int32_t i, t_data *data)
{
	t_env	*lst;

	lst = data->envp_head;
	while (lst != NULL)
	{
		if (ft_strncmp(lst->key, str, i))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static char	*expand_env(t_data *data, char *str, )
{
	size_t	i;
	t_env	*lst;
	int32_t	len;

	i = 0;
	while (str[i])
	{
		while (*str != '$')
			str++;
		while (str[i] != ' ')
			i++;
		lst = cmp_lst(str, i, data);
	}
}

void	count_str