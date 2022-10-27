/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/27 19:02:37 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// just for testing purposes
static void	parser(t_data *data)
{
	data->groupc = 1;
	data->group = calloc(sizeof(t_group), 1);
	data->group[0].full_cmd = ft_calloc(3, sizeof(char *));
	data->group[0].full_cmd[0] = ft_strdup("grep");
	data->group[0].full_cmd[1] = ft_strdup("yo");
	data->group[0].full_cmd[2] = NULL;
	data->group[0].infile = malloc(sizeof(t_infile));
	data->group[0].infile->name = ft_strdup("file1");
	data->group[0].infile->here_doc = true;
	data->group[0].infile->next = NULL;
	// data->group[0].infile->next->name = ft_strdup("file2");
	// data->group[0].infile->next->here_doc = true;
	// data->group[0].infile->next->next = NULL;
	// data->group[0].infile->next->name = "file2";
	// data->group[0].infile->next->here_doc = false;
	// data->group[0].infile->next->next = NULL;
	// data->group[0].outfile = malloc(sizeof(t_outfile));
	// data->group[0].outfile->name = "outfile3";
	// data->group[0].outfile->append = false;
	// data->group[0].outfile = NULL;

	// data->group[0].outfile = malloc(sizeof(t_outfile));
	// data->group[0].outfile->name = "outfile1";
	// data->group[0].outfile->append = false;
	// data->group[0].outfile->next = malloc(sizeof(t_outfile));
	// data->group[0].outfile->next->name = "outfile2";
	// data->group[0].outfile->next->append = false;
	// data->group[0].outfile->next->next = NULL;

	// data->group[1].full_cmd = ft_calloc(3, sizeof(char *));
	// data->group[1].full_cmd[0] = ft_strdup("grep");
	// data->group[1].full_cmd[1] = ft_strdup("file");
	// data->group[1].full_cmd[2] = NULL;
	// data->group[1].outfile = NULL;
	// data->group[1].infile = NULL;
	// data->group[1].infile = malloc(sizeof(t_infile));
	// data->group[1].infile->name = "file2";
	// data->group[1].infile->here_doc = false;
	// data->group[1].infile->next = NULL;
	// data->group[1].infile->next = malloc(sizeof(t_infile));
	// data->group[1].infile->next->name = "file2";
	// data->group[1].infile->next->here_doc = false;
	// data->group[1].infile->next->next = NULL;

	// data->group[1].outfile = malloc(sizeof(t_outfile));
	// data->group[1].outfile->name = "outfile3";
	// data->group[1].outfile->append = false;
	// data->group[1].outfile->next = malloc(sizeof(t_outfile));
	// data->group[1].outfile->next->name = "outfile4";
	// data->group[1].outfile->next->append = true;
	// data->group[1].outfile->next->next = NULL;

	// data->group[1].infile = malloc(sizeof(t_infile *) * 2);
	// data->group[1].infile[0].name = "infile1";
	// data->group[1].infile[1].name = "infile2";

	// data->group[1].outfile = malloc(sizeof(t_outfile *) * 2);
	// data->group[1].outfile->name = "outfile3";
	// data->group[1].outfile->name = "outfile4";
	// data->group[1].outfile[0].next = NULL;
	// data->group[1].outfile[1].next = NULL;
// ------------------------------------------------------------
// 	data->group[1].full_cmd = malloc(sizeof(char *) * 3);
// 	data->group[1].full_cmd[0] = ft_strdup("cd");
// 	data->group[1].full_cmd[1] = ft_strdup("../");
// 	data->group[1].full_cmd[2] = NULL;

// 	data->group[2].full_cmd = malloc(sizeof(char *) * 2);
// 	data->group[2].full_cmd[0] = ft_strdup("echo");
// 	data->group[2].full_cmd[1] = ft_strdup("-nnnnnn");
// 	data->group[2].full_cmd[2] = ft_strdup("-n");
// 	data->group[2].full_cmd[3] = ft_strdup("-nnnnnnn");
// 	data->group[2].full_cmd[4] = ft_strdup("Winnie the Pooneh");
// 	data->group[2].full_cmd[5] = NULL;

// 	data->group[3].full_cmd = malloc(sizeof(char *) * 2);
// 	data->group[3].full_cmd[0] = ft_strdup("export");
// 	data->group[3].full_cmd[1] = ft_strdup("something=blue");
// 	data->group[3].full_cmd[2] = ft_strdup("sosdf=sdfsdf");
// 	data->group[3].full_cmd[3] = ft_strdup("rtwrtw=aaaaaabbnnn");
// 	data->group[3].full_cmd[4] = NULL;

// 	data->group[4].full_cmd = malloc(sizeof(char *) * 2);
// 	data->group[4].full_cmd[0] = ft_strdup("env");
// 	data->group[4].full_cmd[1] = NULL;

// 	data->group[5].full_cmd = malloc(sizeof(char *) * 2);
// 	data->group[5].full_cmd[0] = ft_strdup("unset");
// 	data->group[5].full_cmd[1] = ft_strdup("something");
// 	data->group[5].full_cmd[2] = ft_strdup("sosdf");
// 	data->group[5].full_cmd[3] = NULL;

// 	data->group[6].full_cmd = malloc(sizeof(char *) * 2);
// 	data->group[6].full_cmd[0] = ft_strdup("export");
// 	data->group[6].full_cmd[1] = ft_strdup("something123=red");
// 	data->group[6].full_cmd[2] = NULL;
}

static void	ctrl_c(int32_t sig)
{
	(void)sig;
	rl_replace_line("\n", 1); // test if this works? 
	rl_on_new_line();
	rl_redisplay();
}

static void	ctrl_bslash(int32_t sig)
{
	(void)sig;
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);

}

// "hello $ENV how is it going"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_data	data;
	// char	*str;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(data));
	data.tmp_fd = 0;
	init(&data, envp);
	printf("after init: %p\n", data.envp_head);
	parser(&data);
	execution(&data);
	// char	buf[1000];
	// int fd = open("file1", O_RDONLY, 0666);
	// read(fd, buf, 1000);
	// ft_printf_fd(STDERR_FILENO, "%s", buf);
	// echo(&data, &data.group[2]);

	// export_add(&data, &data.group[3]);
	// unset(&data, &data.group[5]);
	// export_add(&data, &data.group[6]);
	// print_env(&data, data.group);
	// pwd(&data, data.group);
	// printf("%s", get_path(&data));
	// export(&data, &data.group[2]);

	// print_env(&data, &data.group[3]);
	// export(&data, &data.group[2]);
	// while (69)
	// {
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_bslash);
		signal(SIGQUIT, SIG_IGN);
	// 	str = readline("🦇Mishell: ");
	// 	if (str == NULL)
	// 		break ;
	// 	add_history(str);
	// 	free(str);
	// }
	// free_data(&data);
	return (0);
}
