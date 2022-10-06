/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/06 21:11:32 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// just for testing purposes
static void	parser(t_data *data)
{
	data->groupc = 1;
	data->group = malloc(sizeof(t_group) * 2);
	data->group[0].full_cmd = malloc(sizeof(char *) * 2);
	data->group[0].full_cmd[0] = ft_strdup("ls");
	data->group[0].full_cmd[1] = ft_strdup("-la");
	data->group[0].infile = malloc(sizeof(t_infile *) * 2);
	data->group[0].infile[0].name = "infile1";
	data->group[0].infile[1].name = "infile2";
	data->group[0].outfile = malloc(sizeof(t_outfile *) * 2);
	data->group[0].outfile[0].name = "outfile1";
	data->group[0].outfile[1].name = "outfile2";
	data->group[0].builtin = false;
	data->group[1].full_cmd = malloc(sizeof(char *) * 2);
	data->group[1].full_cmd[0] = ft_strdup("grep");
	data->group[1].full_cmd[1] = ft_strdup("file");
	data->group[1].infile = malloc(sizeof(t_infile *) * 2);
	data->group[1].infile[0].name = "infile1";
	// data->group[1].infile[1].name = "infile2";
	data->group[1].outfile = malloc(sizeof(t_outfile *) * 2);
	data->group[1].outfile[0].name = "outfile1";
	data->group[1].outfile[1].name = "outfile2";
	data->group[1].builtin = false;
}

void	ctrl_c(int32_t sig)
{
	(void)sig;
	// printf("test");
	// write(STDIN_FILENO, "", 0);
	rl_on_new_line();
	// rl_redisplay();
}

void	ctrl_slash(int32_t sig)
{
	(void)sig;
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);

}

int32_t	main(void)
{
	t_data	data;
	char	*str;

	while (69)
	{
		// signal(SIGINT, ctrl_c);
		// signal(SIGQUIT, ctrl_slash);
		// signal(SIGQUIT, SIG_IGN);
		str = readline("🦇Minihell: ");
		if (str == NULL)
			break ;
		add_history(str);
		parser(&data);
		// execution(&data);
		free(str);
	}
	return (0);
}
