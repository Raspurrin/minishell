/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:53:56 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/03 21:57:39 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_at_exit(t_data *data)
{
	(void)data;
}

/**
 * Perror uses the errno variable, which is set with an error message
 * by the last malfunctioning function
 * @param error_msg Including an error message of my own.
 * @param yeet If true, this program will exit.
 */
void	display_error(t_data *data, char *error_msg, bool yeet)
{
	perror(error_msg);
	if (yeet == true)
	{
		free_at_exit(data);
		exit(EXIT_FAILURE);
	}
}