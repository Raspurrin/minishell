/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 03:43:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/20 18:12:17 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int32_t	open_file(t_data *data, int32_t flags, char *name)
{
	int32_t	fd;

	fd = open(name, flags, 0666);
	if (fd == -1)
		return (display_error(NODIR, join_err(name, NULL), \
											data, NULL), 1);
	return (fd);
}

/**
 * A heredoc is a file literal. It is a multi-line string taken from STDIN
 * ended by a delimiter. It is then treated as an input file.
 * I create a temporary file where I store everything until the delimiter
 * is used and then delete it 
 */
static int32_t	here_doc(t_data *data, t_infile *lst)
{
	int32_t		fd;
	char		*line;

	(void)data;
	fd = open_file(data, (O_RDWR | O_CREAT | O_TRUNC), lst->name);
	while (true)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (unlink(lst->name), 0);
		if (ft_strncmp(line, lst->name, ft_strlen(lst->name) + 1) == 10)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	fd = open(lst->name, O_RDONLY, 0666);
	return (fd);
}

bool	infiles(t_data *data, t_group *group, t_fds *fds)
{
	int32_t		fd;
	t_infile	*lst;

	lst = group->infile;
	(void)data;
	while (lst != NULL)
	{
		if (lst->here_doc == true)
			fd = here_doc(data, lst);
		else
			fd = open_file(data, O_RDONLY, lst->name);
		if (lst->next == NULL)
		{
			if (fds)
			{
				fds->infile = fd;
				fds->std_in = dup(STDIN_FILENO);
			}
			return (dup2(fd, STDIN_FILENO), close(fd), true);
		}
		close(fd);
		lst = lst->next;
	}
	return (false);
}

/**
 * @brief I check whether or not the outfile should use append mode.
 * And I always create the file, but I only consider the output of the 
 * last output file. Dup duplicates it to STDOUT: 
 * 0 - STDIN		->	0 - STDIN
 * 1 - STDOUT 			1 - fd		<- this temporarily closes STDOUT.
 * 2 - STDERR			2 - STDERR
 * 3 - fd 
 * @param group 
 */
bool	outfiles(t_data *data, t_group *group, t_fds *fds)
{
	int32_t		fd;
	t_outfile	*lst;

	(void)data;
	lst = group->outfile;
	while (lst != NULL)
	{
		if (lst->append == true)
			fd = open_file(data, (O_RDWR | O_CREAT | O_APPEND), lst->name);
		else
			fd = open_file(data, (O_RDWR | O_CREAT | O_TRUNC), lst->name);
		if (lst->next == NULL)
		{
			if (fds)
			{
				fds->outfile = fd;
				fds->std_out = dup(STDOUT_FILENO);
			}
			return (dup2(fd, STDOUT_FILENO), close(fd), true);
		}
		close(fd);
		lst = lst->next;
	}
	return (false);
}
