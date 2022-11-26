/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/25 19:36:23 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * if PWD is unset OLDPWD's value changes to ""
 * Otherwise OLDPWD gets PWD's old value before I change PWD's value in cd.
 */
static void	update_pwd(t_data *data)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = find_node(data->envp_head, "OLDPWD");
	pwd = find_node(data->envp_head, "PWD");
	if (oldpwd && oldpwd->value)
		free(oldpwd->value);
	if (!pwd)
		oldpwd->value = "";
	else
	{
		oldpwd->value = pwd->value;
		if (pwd && pwd->value)
			free(pwd->value);
		pwd->value = get_pwd();
	}
}

/**
 * Chdir returns -1 if the path cannot be changed. It can accept relative paths. 
 * Oldpwd will be changed first, then I check if the path already works,
 * in case of an absolute path given, otherwise the relative path will be solved.
 * If PWD is not unset, the value will be changed as well.
 * data->pwd exists in case PWD doesn't, since pwd should still work.
*/
uint32_t	cd(t_data *data, t_group *group)
{
	t_env	*env;

	if (!group->full_cmd[1])
	{
		env = find_node(data->envp_head, "HOME");
		if (env && env->value)
			chdir(env->value);
	}
	else if (chdir(group->full_cmd[1]) == -1)
	{
		fprintf(stderr, "pwd: %s\n", group->full_cmd[1]);
		return (display_error(NODIR, join_err(NULL, NULL), NULL, group), 1);
	}
	update_pwd(data);
	return (0);
}
