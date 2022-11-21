/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:53:56 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/21 14:02:43 by mialbert         ###   ########.fr       */
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
	str[0] = str1;
	str[1] = str2;
	return (str);
}

/**
 * @param nbr The number of the element the error message can be found in.
 * If set to -1, perror will be used instead.
 * @param str Contains two strings, the first will be placed before the errno
 * message and the second afterwards.
 */
static void	errno(int8_t nbr, char *str[2])
{
	char				*err;
	static const char	*errors[] = {
		"",
		": command not found",
		": syntax error near unexpected token",
		"is a directory",
		"no such file or directory: ",
		": not a valid identifier",
		": event not found",
		": invalid option",
		": too many arguments",
		"HOME not set",
		": permission denied",
		": numeric argument required"
	};

	if (nbr == -1)
	{
		err = gnl_strjoin(PROMPT, str[0]);
		return (perror(err), free(str), free(err));
	}
	this_is_debug_yo();
	ft_printf_fd(STDERR_FILENO, "%s%s%s%s @ %s (line: %d)\n", \
				PROMPT, str[0], errors[nbr], str[1], __FILE__, __LINE__);
	free(str);
}

/**
 * @param data The data struct to be potentially yeeted.
 * @param nbr The errno number corresponding to an error message in errno().
 * If set to -1, perror will be used.
 * @param yeet If true, this program will free all allocated memory and exit.
 * @param str An array of two strings, if set to something the first will be 
 * displayed before the errno message and the second afterwards. if not desired,
 * set one or both to "".
 */
void	display_error(t_data *data, int8_t nbr, bool yeet, char *str[])
{
	errno(nbr, str);
	if (yeet)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
}
