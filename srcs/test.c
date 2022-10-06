/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/06 00:50:01 by mialbert         ###   ########.fr       */
=======
/*   Updated: 2022/10/05 17:17:56 by pmoghadd         ###   ########.fr       */
>>>>>>> 3d29450e6711ad2f4aedfdd8cae3737ef8afdee6
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// just for testing purposes
void	parser(char *str, t_data *data)
{
	data->argc = 2;
	data->args = malloc(sizeof(t_arg) * data->argc);
	data->args->infile
}

int32_t	main(void)
{
	t_data	data;
	char	*str;
<<<<<<< HEAD

	while (true)
=======
	//dfdsf jdsfoaijsdsdfsdf dfdfdfdf
	while (6942)
>>>>>>> 3d29450e6711ad2f4aedfdd8cae3737ef8afdee6
	{
		str = readline("\e[38;5;20m🦇Minihell: \e[0m");
		if (str == NULL)
			break ;
		add_history(str);
		parser(str);
		// execution(&data);
		free(str);
	}
	return (0);
}
