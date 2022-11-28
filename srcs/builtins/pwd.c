/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/28 21:42:50 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_oldpwd(t_data *data)
{
	t_env	*env;
	t_env	*new;

	env = find_node(data->envp_head, "OLDPWD");
	if (env && env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	if (env)
		env->value = NULL;
	if (env && env->keyvalue)
	{
		free(env->keyvalue);
		env->keyvalue = ft_strdup("OLDPWD");
	}
	else
	{
		new = ft_calloc(1, sizeof(t_env));
		new->keyvalue = ft_strdup("OLDPWD");
		new->key = ft_strdup("OLDPWD");
		new->value = NULL;
		lst_addback(data, new);
	}
}

/**
 * I just use getcwd to get the current working directory.
 * I allocate 100 for the buffer used in getcwd, and realloc
 * more if needed.
 */
char	*get_pwd(void)
{
	size_t	size;
	size_t	old_size;
	char	*pwd;

	size = 100;
	pwd = malloc(size);
	if (!pwd)
		return (NULL);
	while (true)
	{
		pwd = getcwd(pwd, size);
		if (pwd)
			break ;
		old_size = size;
		size += 100;
		free(pwd);
		pwd = ft_realloc_n(pwd, size, old_size);
		if (!pwd)
			return (NULL);
	}
	return (pwd);
}

uint32_t	pwd(t_data *data, t_group *group)
{
	char	*pwd;

	(void)group;
	(void)data;
	pwd = get_pwd();
	if (!pwd)
		return (free(pwd), 1);
	ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
	return (free(pwd), 0);
}
