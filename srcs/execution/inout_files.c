/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/07 19:04:55 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc(t_group *group)
{
	(void)group;
	return ;
}

void	infiles(t_data *data, t_group *group)
{
	size_t	i;
	int32_t	fd;

	i = 0;
	fd = 0;
	(void)data;
	while (i < group->infilec)
	{
		if (group->infile[i].here_doc == true)
			here_doc(group);
		else
		{
			if (open(group->infile[i].name, O_RDWR, 0666) == -1)
				display_error(data, "Opening infile failed", true);
		}
		i++;
	}
	dup2(fd, STDIN_FILENO);
}

void	outfiles(t_group *group, int32_t fd[2])
{
	size_t	i;
	int32_t	outfile;

	i = 0;
	outfile = 0;
	if (group->outfilec == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		return ;
	}
	while (i < group->outfilec)
	{
		if (group->outfile->append == true)
			outfile = open(group->outfile[i].name, O_RDWR | O_CREAT \
													| O_APPEND, 0666);
		else
			outfile = open(group->outfile[i].name, O_RDWR | O_CREAT, 0666);
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
}

/**
 * A heredoc is a file literal. It is a multi-line string taken from STDIN
 * ended by a delimiter. It is then treated as an input file.
 * I create a temporary file where I store everything until the delimiter
 * is used and then delete it 
 */
// static void	here_doc(t_data *data)
// {
// 	char	*line;

// 	line = ft_calloc(2, 1);
// 	data->infile = open(data->argv[1], O_RDWR | O_CREAT, 0666);
// 	if (data->infile == -1)
// 		display_error(data, "Heredoc inout_files, Open infile failed", true);
// 	while (ft_strncmp(line, data->argv[2], ft_strlen(data->argv[2]) + 1) != 10)
// 	{
// 		free(line);
// 		line = get_next_line(STDIN_FILENO);
// 		write (data->infile, line, ft_strlen(line));
// 	}
// 	free(line);
// 	dup2(data->infile, STDIN_FILENO);
// 	data->outfile = open(data->argv[data->argc - 1], O_RDWR | O_CREAT \
// 														| O_APPEND, 0666);
// 	if (data->outfile == -1)
// 		display_error(data, "Bonus inout_files, Open outfile failed", false);
// 	unlink("./here_doc");
// }

// int32_t	inout_files(t_data *data)
// {
// 	if (ft_strncmp(data->argv[1], "here_doc", 9) == 0)
// 		return (here_doc(data), 1);
// 	else
// 	{
// 		data->infile = open(data->argv[1], O_RDONLY, 0666);
// 		if (data->infile == -1)
// 			display_error(data, "Bonus inout_files, Open infile failed", \
// 																	true);
// 		data->outfile = open(data->argv[data->argc - 1], O_RDWR | O_CREAT \
// 															| O_TRUNC, 0666);
// 		if (data->outfile == -1)
// 			display_error(data, "Bonus inout_files, Open outfile failed", \
// 																	false);
// 	}
// 	dup2(data->infile, STDIN_FILENO);
// 	return (0);
// }
