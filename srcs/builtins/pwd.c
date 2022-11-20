/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:49 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 01:58:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Initialise data->pwd with the size of the current working directory
 * to later use this to determine the buffer size of get_cdw(), which 
 * gets the current working directory for you.
 */
void	init_pwd_size(t_data *data)
{
	t_env	*env;

	env = find_node(data->envp_head, "PWD");
	if (!env || !env->value)
		return ;
	data->pwd_size = ft_strlen(env->value) + 1;
	printf("pwd size: %zu\n", data->pwd_size);
}

char	*get_pwd(size_t buf_size)
{
	char	*buf;

	buf = malloc(buf_size);
	return (getcwd(buf, buf_size));
}

/**
 * @brief getcwd gets the current working directory, so I just keep 
 * track of the right buffer size when changing directories and print the
 * result of the function.
 */
void	pwd(t_data *data, t_group *group)
{
	char	*buf;

	(void)group;
	buf = get_pwd(data->pwd_size);
	ft_printf_fd(STDOUT_FILENO, "%s\n", buf);
	free (buf);
}
