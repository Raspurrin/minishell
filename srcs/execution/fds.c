/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:48:19 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/23 01:07:33 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_data *data, size_t i, int32_t fd[2])
{
	close(fd[WRITE]);
	if (i > 0)
		close(data->tmp_fd);
	if (i == data->groupc - 1)
		close(fd[READ]);
}

void	free_fds(void)
{
	int	i;

	i = 3;
	while (i <= 4096)
		close(i++);
}
