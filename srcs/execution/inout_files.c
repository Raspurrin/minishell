/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/14 01:35:01 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc(t_infile *lst)
{
	(void)lst;
	return ;
}

void	infiles(t_data *data, t_group *group)
{
	int32_t		fd;
	t_infile	*lst;

	fd = 0;
	lst = group->infile;
	while (lst != NULL)
	{
		if (lst->here_doc == true)
			here_doc(lst);
		else
		{
			fd = open(lst->name, O_RDWR, 0666);
			if (fd == -1)
				display_error(data, "Opening infile failed", true);
			if (lst->next == NULL)
				dup2(fd, STDIN_FILENO);
			close (fd);
		}
		lst = lst->next;
	}
}

void	outfiles(t_group *group)
{
	int32_t		fd;
	int16_t		flag;
	t_outfile	*lst;

	lst = group->outfile;
	while (lst != NULL)
	{
		if (lst->append == true)
			flag = (O_RDWR | O_CREAT | O_APPEND);
		else
			flag = (O_RDWR | O_CREAT | O_TRUNC);
		fd = open(lst->name, flag, 0666);
		if (lst->next == NULL)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		lst = lst->next;
	}
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
