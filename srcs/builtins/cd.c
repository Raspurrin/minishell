/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 01:15:11 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief ex: str: "my_projects/minishell" c: '/' 
 * it would return the length of "my_projects": 11
 * @return The length from the start of the string to c, 0 if
 * str or c is empty or the length of the string if c is not found
 */
static size_t	end_to_char_len(char *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str || !*str || !c)
		return (0);
	len = ft_strlen(str) + 1;
	while (len-- > 0)
	{
		if (str[len] == 'c')
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief ex: str: "my_projects/minishell" c: '/' 
 * it would return the length of "minishell": 9
 * @return The length from the end of the string to c  0 if
 * str or c is empty or the length of the string if c is not found
 */
static size_t	begin_to_char_len(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str || !*str || !c)
		return (0);
	while (str[i])
	{
		if (str[i] == 'c')
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief ../../something/yoo/../yoo./././ha
 * /Users/mialbert/Documents/my_projects/minishell
 * @return size_t 
 */
static size_t	get_pwd_size(char *relative, char *pwd, size_t size)
{
	size_t	i;
	size_t	dir_len;

	i = 0;
	dir_len = 0;
	if (!pwd || !*pwd || !relative || !*relative)
		return (0);
	while (*relative)
	{
		if (ft_strncmp(relative, "./", 2) == 0)
			relative += 2;
		else if (ft_strncmp(relative, "../", 2) == 0)
		{
			size -= end_to_char_len(pwd, '/');
			relative += 2;
		}
		else
		{
			dir_len = begin_to_char_len(pwd, '/');
			size += dir_len;
			relative += dir_len;
		}
	}
	return (size);
}

/**
 * if PWD is unset OLDPWD's value changes to ""
 * Otherwise OLDPWD gets PWD's old value before I change PWD's value in cd.
 */
static void	update_oldpwd(t_data *data)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = find_node(data->envp_head, "OLDPWD");
	pwd = find_node(data->envp_head, "PWD");
	if (!pwd)
		oldpwd->value = "";
	else
		oldpwd->value = pwd->value;
}

/**
 * Chdir returns -1 if the path cannot be changed. It can accept relative paths. 
 * Oldpwd will be changed first, then I check if the path already works,
 * in case of an absolute path given, otherwise the relative path will be solved.
 * If PWD is not unset, the value will be changed as well.
 * data->pwd exists in case PWD doesn't, since pwd should still work.
*/
void	cd(t_data *data, t_group *group)
{
	char	*pwd;

	pwd = get_pwd(data->pwd_size);
	if (chdir(group->full_cmd[1]) == -1)
		return (perror(NULL));
	update_oldpwd(data);
	data->pwd_size = get_pwd_size(group->full_cmd[1], pwd, data->pwd_size);
	free (pwd);
}
