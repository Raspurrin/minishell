/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:53:56 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 23:33:12 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Adding two strings to an array of strings of two elements (*str[2])
 * To be used as parameter for display_error()
 */
char	**join_err(char *str1, char *str2)
{
	char	**str;

	str = ft_calloc(2, sizeof(char *));
	if (str1)
		str[0] = ft_strjoin(str1, ": ");
	else
		str[0] = "";
	if (str2)
		str[1] = ft_strjoin(": ", str2);
	else
		str[1] = "";
	return (str);
}

/**
 * @param nbr The number of the element the error message can be found in.
 * If set to -1, perror will be used instead.
 * @param str Contains two strings, the first will be placed before the errno
 * message and the second afterwards.
 */
static void	errno(t_group *group, uint8_t nbr, char *str[2])
{
	static const char	*errors[] = {
		"",
		"command not found",
		"syntax error near unexpected token",
		"is a directory",
		"No such file or directory",
		"not a valid identifier",
		"event not found",
		"invalid option",
		"too many arguments",
		"HOME not set",
		"permission denied",
		"numeric argument required",
		"undefined error"
	};

	if (nbr > ERR_COUNT)
		nbr = ERR_COUNT;
	if (group && group->builtin)
		ft_printf_fd(STDERR_FILENO, "%s%s: %s%s%s\n", \
					PROMPT, group->full_cmd[0], str[0], errors[nbr], str[1]);
	else
		ft_printf_fd(STDERR_FILENO, "%s%s%s%s\n", \
								PROMPT, str[0], errors[nbr], str[1]);
	free(str);
}

/**
 * @param nbr The errno number corresponding to an error message in errno().
 * If set to -1, perror will be used and str[0] can be used for an extra msg.
 * @param str An array of two strings, if set to something the first will be 
 * displayed before the errno message and the second afterwards. if not desired,
 * set one or both to NULL.
 * @param data Data struct to be yeeted if not set to NULL and then it exits.
 * @param group Pass the group struct if the function is a builtin, so
 * additional info for error messages can be retrieved.
 */
void	display_error(int8_t nbr, char *str[], t_data *data, t_group *group)
{
	char	*err;

	this_is_debug_yo();
	errno(group, nbr, str);
	if (nbr == -1)
	{
		err = ft_strjoin_str2(PROMPT, str[0]);
		return (perror(err), free(str), free(err));
	}
	if (data)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
}
