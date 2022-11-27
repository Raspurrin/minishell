/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:10:18 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 23:30:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_key(t_group *group, char *key, char *next_key)
{
	if (*key == '=')
		return (false);
	while (*key)
	{
		if ((!(ft_isalpha(*key)) && (!ft_isalnum(*key)) \
					&& *key != ' ' && *key != '_' && *key != '='))
		{
			g_exitcode = 1;
			display_error(IDENT, join_err(key, \
											NULL), NULL, group);
			if (!next_key)
				return (false);
		}
		key++;
	}
	return (true);
}

bool	dup_key(t_env *envp_head, char **tmp, char *keyvalue)
{
	t_env	*dup;

	dup = find_node(envp_head, tmp[0]);
	if (!dup)
		return (false);
	free(dup->keyvalue);
	if (tmp[1])
	{
		free(dup->value);
		dup->value = tmp[1];
	}
	dup->keyvalue = ft_strdup(keyvalue);
	free(tmp[0]);
	free(tmp);
	return (true);
}

/**
 * example:
 * export something=====blue something= USER=mialbert
 */
uint32_t	export_add(t_data *data, t_group *group)
{	
	size_t	i;
	char	**tmp;
	t_env	*new;

	i = 1;
	while (group->full_cmd[i])
	{
		if (!check_key(group, group->full_cmd[i], group->full_cmd[i + 1]))
			return (g_exitcode);
		else
		{
			tmp = env_split(group->full_cmd[i], '=');
			if (!dup_key(data->envp_head, tmp, group->full_cmd[i]))
			{
				new = ft_calloc(1, sizeof(t_env));
				env_addvalue(new, tmp, group->full_cmd[i]);
				lst_addback(data, new);
			}
		}
		i++;
	}
	return (g_exitcode);
}
