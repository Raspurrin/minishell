/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:04:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/21 22:20:38 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(bool	newline, char **str)
{
	size_t	i;

	i = 0;
	while ((str[i]))
	{
		if (i != 0)
			printf(" ");
		printf("%s", str[i]);
		i++;
	}
	if (newline)
		printf("\n");
}

/**
 * If I find a valid "-n", I move the pointer of echo to skip it,
 * so it won't be printed in print_echo(). 
 * @param echo Array of strings containing everything after "echo"
 * ex: from "echo -nnn --n--n hi", you would get "-nnn --n--n hi"
 * @return True if there is a newline
 * @return False if not.
 */
bool	check_flag(char	***echo)
{
	bool	newline;
	size_t	i;

	i = 1;
	newline = true;
	while ((**echo && ft_strncmp("-n", (**echo), 2) == 0))
	{
		while ((**echo)[i])
		{
			if ((**echo)[i++] != 'n')
				return (newline);
		}
		(*echo)++;
		newline = false;
		i = 1;
	}
	return (newline);
}

/**
 * @brief Echo prints out whatever comes afterwards with a newline 
 * char afterwards. -n cancels out this newline character.
 * This is only registered with one '-' and any amount of 'n'
 * anything in between cancels it out
 * Valid newline cancel: echo -n -n -nnnnnn -nn Hello
 * Invalid: echo -nnnn-n Hello
 */
uint32_t	echo(t_data *data, t_group *group)
{
	bool	newline;
	char	**echo;
	size_t	i;

	(void)data;
	i = 1;
	newline = true;
	echo = group->full_cmd;
	if (!echo || !*echo)
		return (false);
	if (!echo || !echo[1])
	{
		echo[0] = ft_strdup("");
		return (print_echo(newline, echo), true);
	}	
	echo++;
	newline = check_flag(&echo);
	return (print_echo(newline, echo), true);
}
