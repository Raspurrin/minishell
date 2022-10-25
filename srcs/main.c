/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/25 19:25:05 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// static void	ctrl_c(int32_t sig)
// {
// 	(void)sig;
// 	printf("test");
// 	write(STDIN_FILENO, "", 0);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

static void	ctrl_bslash(int32_t sig)
{
	(void)sig;
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;
	char	*str;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(data));
	init(&data, envp);
	while (69)
	{
		// signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_bslash);
		signal(SIGQUIT, SIG_IGN);
		str = readline("🦇Mishell: ");
		if (str == NULL)
			break ;
		add_history(str);
		// parser(&data);
		// execution(&data, envp);
		free(str);
	}
	free_data(&data);
	return (0);
}
