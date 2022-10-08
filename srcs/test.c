/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:07:48 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/08 20:15:44 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

// just for testing purposes
// void	parser(char *str, t_data *data)
// {
// 	data->argc = 2;
// 	data->args = malloc(sizeof(t_arg) * data->argc);
// 	data->args->infile
// }

// t_token	*lstnew(void *content)
// {
// 	t_token	*ptr;

// 	ptr = malloc(sizeof(t_token));
// 	if (!ptr)
// 		return (NULL);
// 	(*ptr).content = content;
// 	(*ptr).next = NULL;
// 	return (ptr);
// }


void	print_linkedlist(t_token *data)
{
	t_token	*tmp;
	size_t	i;

	tmp = data;
	i = 0;
	while (tmp->next != NULL)
	{
		printf("i: %zu   element:%s\n", i, tmp->infile->name[0]);
		tmp = tmp->next;
	}
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

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

int	length_of_word(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

void	initialize(t_token	*data)
{
	data = (t_token *)malloc(sizeof(t_token));
 	if (!data)
		return ; //error management?
	// data->counter_infile = 0;
	// data->counter_outfile = 0;
	data->next = NULL;
}

void	erase_specialchars(char *s, char c)
{
	char	*word;
	int		i;
	int		l;
	t_token *data;

	i = 0;
	l = length_of_word(s, c);
	word = malloc(sizeof(char) * (l + 1));
	data = (t_token *)malloc(sizeof(t_token));
	if (s[i] == c)
	{
		while (s[i + 1] != c)
		{
			word[i] = s[i + 1];
			i++;
		}
		word[i] = '\0';
		data->command = ft_strdup(word);
		free(word);
		printf("word is : %s \n", data->command);
		data->next = NULL;
	}
	// if (word)
	// 	return (s + i);
	// return (NULL);
}

int	find_next(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	add_infile(char *s, t_infile **new, int k)
{
	int	space;
	int	l;

	if (s[0] == '<')
	{
		space = skip_spaces(s + 1);
		l = find_next(s + space + 1, ' ');
		(*new)->here_doc[k] = 1;
		(*new)->name[k]= ft_substr(s + 1, space, l);
		printf("Inputs:   %s, k:   %d,  heredoc:   %d\n",(*new)->name[k], k,(*new)->here_doc[k]);
		return (space + l + 1);
	}
	else
	{
		space = skip_spaces(s);
		l = find_next(s + space, ' ');
		(*new)->name[k]= ft_substr(s, space, l);
		(*new)->here_doc[k] = 0;
	}
    printf("Inputs:   %s, k:   %d,  heredoc:   %d\n",(*new)->name[k], k,(*new)->here_doc[k]);
	return (space + l);
}

int	add_outfile(char *s, t_outfile	**new, int k)
{
	int	space;
	int	l;

	if (s[0] == '>')
	{
		space = skip_spaces(s + 1);
		l = find_next(s + space + 1, ' ');
		(*new)->append[k] = 1;
		(*new)->name[k]= ft_substr(s + 1, space, l);
		printf("outputfile:   %s, k%d,  append   %d\n",(*new)->name[k], k, (*new)->append[k]);
		return (space + l + 1);
	}
	else
	{
		space = skip_spaces(s);
		l = find_next(s + space, ' ');
		(*new)->append[k] = 0;
		(*new)->name[k]= ft_substr(s, space, l);
	}
    printf("outputfile:   %s, k   %d, append   %d\n",(*new)->name[k], k, (*new)->append[k]);
	return (space + l);
}

void	initialize_in_out(t_infile **new_in, t_outfile **new_out, t_token *data)
{
	*new_in = (t_infile *)malloc(sizeof(t_infile));
	*new_out = malloc(sizeof(t_outfile));
	data->infile = ft_calloc(sizeof(t_infile), 1);
	data->outfile = (t_outfile *)ft_calloc(sizeof(t_outfile),1);
	(*new_in)->name = ft_calloc(sizeof(char *), 100);
	(*new_out)->name = ft_calloc(sizeof(char *), 100);
	(*new_out)->name = ft_calloc(sizeof(char *), 100);
	(*new_in)->here_doc = (bool *)malloc(sizeof(bool));
	(*new_out)->append = (bool *)malloc(sizeof(bool));
	data->counter_infile = 0;
	data->counter_outfile = 0;
	data->read_in = 0;
	data->read_out = 0;
}

void	replace_chars(char *s, char c, int length)
{
	int	i;

	i = 0;
	while (i <= length)
	{
		s[i] = c;
		i++;
	}
}

void extract_words(t_token	*data, char *s)
{
	int i = 0;
	
	data->command_ops = ft_split(s, ' ');
	while (data->command_ops[i])
	{
		printf("words:   %s\n",data->command_ops[i]);
		i++;
	}
}

void	make_token(char *s, t_token *data)
{
	int		i;
	t_infile	*new_in;
	t_outfile	*new_out;
	t_token	**head;

	head = &data;
	i = 0;
	initialize(data);
	initialize_in_out(&new_in, &new_out, data);
	while (s[i])
	{
		if (s[i] == '<')
		{
            data->read_in = add_infile(s + i + 1, &new_in, data->counter_infile);
            data->counter_infile++;
			if (s[i + 1] == '<')
				i++;
			replace_chars(s + i, ' ', data->read_in);
        }
		if (s[i] == '>')
		{
			data->read_out = add_outfile(s + i + 1, &new_out, data->counter_outfile);
			data->counter_outfile++;
			replace_chars(s + i, ' ', data->read_out);
			if (s[i + 1] == '>')
				i++;
		}
        i++;
	}
	extract_words(data, s);
	data->infile = new_in;
	data->outfile = new_out;
	data->next = NULL;
	lstadd_back(head, data);
	// data = data->next;
	data = *head;
	// print_linkedlist(*head);
	printf("list is: first in:%s first out:%s\n", (*head)->infile->name[0], (*head)->outfile->name[0]);
}


int32_t	main(void)
{
	char	*str;
	int		i;
	char	**pipe_wise_splitted;
	t_token	data;
	// t_token	*head;

	// head = &data;
	i = 0;
	// initialize(&data);
	while (1000)
	{
		str = readline(" Minihell: ");
		if (str == NULL)
			break ;
		add_history(str);
		pipe_wise_splitted = ft_split(str, '|');
		while (pipe_wise_splitted[i])
		{
			make_token(pipe_wise_splitted[i], &data);
			i++;
		}
		// data = *head;
		// print_linkedlist(&data);
		free(str);
	}
	return (0);
}
