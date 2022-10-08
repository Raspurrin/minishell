/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:22:30 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 04:45:27 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(t_data *data, t_group *group)
{
	if (ft_strncmp("../", group->full_cmd[1], 3) && data->dirp)
		closedir(data->dirp);
	else
		data->dirp = opendir(group->full_cmd[1]);
}
