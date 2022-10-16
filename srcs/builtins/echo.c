/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:04:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/15 17:59:51 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(bool	newline, char **str)
{
	while ((*str))
	{
		printf("%s", *str);
		str++;
	}
	if (newline)
		printf("\n");
}

/**
 * @brief Echo prints out whatever comes afterwards with a newline 
 * char afterwards. -n cancels out this newline character.
 * This is only registered with one '-' and any amount of 'n'
 * anything in between cancels it out
 * Valid newline cancel: echo -n -n -nnnnnn -nn Hello
 * Invalid: echo -nnnn-n Hello
 */
void	echo(t_data *data, t_group *group)
{
	bool	newline;
	size_t	i;

	i = 1;
	(void)data;
	newline = !false;
	group->full_cmd++;
	while ((ft_strncmp("-n", (*group->full_cmd), 2) == 0) && *group->full_cmd)
	{
		while ((*group->full_cmd)[i])
		{
			if ((*group->full_cmd)[i++] != 'n')
				return (print_echo(newline, group->full_cmd));
		}
		group->full_cmd++;
		newline = !true;
		i = 1;
	}
	return (print_echo(newline, group->full_cmd));
}
