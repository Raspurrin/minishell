/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/11 00:10:31 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>



// void	print_linkedlist(t_token *data)
// {
// 	t_token	*tmp;
// 	size_t	i;

// 	tmp = data;
// 	i = 0;
// 	while (tmp->next != NULL)
// 	{
// 		printf("i: %zu   element:%s\n", i, tmp->infile->name[0]);
// 		tmp = tmp->next;
// 	}
// }

void	lstaddback(t_infile **lst, t_infile *new)
{
	t_infile	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{	
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lstaddback_out(t_outfile **lst, t_outfile *new)
{
	t_outfile	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{	
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ( s[i] == ' ' || s[i] == '\t'
		|| s[i] == '\n')) //add all the white spaces
		i++;
	return (i);
}

void	add_data_to_group(t_token	*data, t_group	*for_djaisin, int i)
{
	for_djaisin[i].infile = data->infile;
	for_djaisin[i].outfile = data->outfile;
	for_djaisin[i].full_cmd = data->command_ops;
	for_djaisin[i].infilec = data->counter_infile;
	for_djaisin[i].outfilec = data->counter_outfile;
	printf("adle ali:%s\n", for_djaisin[i].full_cmd[0]);
	
}

void	make_token(char *s, t_group *data, int index)
{
	int		i;
	t_group	*info;
	
	i = 0;
	info = (t_group *)malloc(sizeof(t_group));
	if (!info)
		return ;
	initialize(&info);
	while (s[i])
	{
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			info->read_in = special_chars(&info, s + i);
			i = i + info->read_in + 1;
		}
		else if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			info->read_in = quoted_word_extract(&info, s + i);
			i = i + info->read_in;
		}
		else if (s[i] && s[i] != ' ')
		{
			info->read_in = normal_word_extract(&info, s + i);
			i = i + info->read_in;
		}
        i++;
	}
}

int32_t	main(void)
{
	char	*str;
	int		i;
	char	**pipe_wise_splitted;
	t_group	data;

	
	i = 0;
	while (1000)
	{
		str = readline(" Minihell: ");
		if (str == NULL)
			break ;
		add_history(str);
		pipe_wise_splitted = ft_split(str, '|');
		while (pipe_wise_splitted[i])
		{
			make_token(pipe_wise_splitted[i], &data, i);
			i++;
		}
		free(str);
	}
	return (0);
}
