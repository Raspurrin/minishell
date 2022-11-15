/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/15 14:57:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static void	init(t_data *data, char **envp)
{
	ft_printf_fd(STDERR_FILENO, "in init\n");
	ft_bzero(data, sizeof(data));
	data->paths = NULL;
	env_innit(data, envp);
	ft_printf_fd(STDERR_FILENO, "after env_innit\n");
	path_innit(data);
	ft_printf_fd(STDERR_FILENO, "after path_innit\n");
	init_pwd(data);
}

/**
 * WIFSIGNALED indicates that the child process exited because it raised a 
 * signal. 
 * WTERMSIG returns the value of the signal raised by the child process.
 * If SIGINT (interrupt/CTRL-C) was raised, it adds 128 to the exit code.
 */
void	set_exitcode(t_data *data)
{
	if (WIFSIGNALED(data->status))
	{
		if (WTERMSIG(data->status) == SIGINT)
			data->status = 128 + WTERMSIG(data->status);
	}
}

// static void	ctrl_c(int32_t sig)
// {
// 	(void)sig;
// 	ft_printf_fd(STDOUT_FILENO, "\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay(); // not sure if this is fine or not
// }

// static void	ctrl_bslash(int32_t sig)
// {
// 	(void)sig;
// 	rl_redisplay();
// 	signal(SIGQUIT, SIG_IGN);
// }

void	free_fds()
{
	int	i;

	i = 3;
	while (i <= 4096)
		close(i++);
}

void	free_fds()
{
	int	i;

	i = 3;
	while (i <= 4096)
		close(i++);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	// char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	init(&data, envp);
	if (argv[1])
	{
		ft_printf_fd(STDERR_FILENO, "after if argv[1]\n");
		fake_parser(&data, argv[1]);
		execution(&data);
	}
	// else
	// {
	// 	while (69)
	// 	{
	// 		// signal(SIGINT, ctrl_c);
	// 		// signal(SIGQUIT, ctrl_bslash);
	// 		signal(SIGQUIT, SIG_IGN);
	// 		str = readline("🦇Mishell: ");
	// 		if (str == NULL)
	// 			return (printf("exit\n"), 0);
	// 		if (ft_strncmp(str, "./minishell", 12))
	// 			execution(&data);
	// 		// str = ft_strdup("export hi | env");
	// 		// parser(&data, str);
	// 		add_history(str);
	// 		free(str);
	// 	}
	// }
	free_data(&data);
	return (0);
}
