/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/17 15:07:41 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../includes/minishell.h"

void executing(t_group *info) //just for test purposes
{
	int	y;
	t_outfile	*head = info->outfile;

	y = 0;
	while (info->full_cmd[y])
	{
		printf("i   %d    word|%s|\n", y, info->full_cmd[y]);
		y++;
	}
	while (info->outfile != NULL)
	{
		printf("info->outfiles|%s|\n", info->outfile->name);
		info->outfile = info->outfile->next;
	}
	info->outfile = head;
	while (info->infile != NULL)
	{
		printf("info->infiles|%s|\n", info->infile->name);
		info->infile = info->infile->next;
	}
}

void	make_token(t_data *data, char *s, t_group *info, int index)
{
	int		i;

	i = 0;
	(void)info;
	(void)index;
	(void)data;
	initialize(&info, index, data->envp_head);
	while (s[i])
	{
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			info->read_in = special_chars(data, &info, s + i);
			i = i + info->read_in + 1;
		}
		else if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			info->read_in = quoted_word_extract(data, &info, s + i);
			i = i + info->read_in;
		}
		else if (s[i] && s[i] != ' ')
		{
			info->read_in = normal_word_extract(data, &info, s + i);
			i = i + info->read_in;
		}
		i++;
	}
	info->full_cmd[info->commandc] = NULL;
	executing(info); //parsed data is passed to execution.
}

void	parser(t_data *data, char *str)
{
	int		i;
	char	**pipe_wise_splitted;
	i = 0;
	check_input_before_handling(str);
	pipe_wise_splitted = ft_split_shell(str, '|');
	first_initialization(pipe_wise_splitted, &(data->group));
	while (pipe_wise_splitted[i])
	{
		make_token(data, pipe_wise_splitted[i], &(data->group[i]), i);
		i++;
	}
	printf("test for the array of struct%s\n", data->group[0].full_cmd[0]);
}
