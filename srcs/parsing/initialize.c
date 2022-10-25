/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:01:38 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/25 19:00:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialize(t_group	**data)
{
    // data = (t_group *)malloc(sizeof(t_group));
    // if (!data) //error
    //     return ;
	(*data)->infile = ft_calloc(sizeof(t_infile), 1);
	(*data)->outfile = (t_outfile *)ft_calloc(sizeof(t_outfile),1);
	(*data)->infile->name = (char *)malloc(sizeof(char) * 100);
	(*data)->outfile->name = ft_calloc(sizeof(char), 100);
	(*data)->infile->here_doc = (bool *)malloc(sizeof(bool));
	(*data)->outfile->append = (bool *)malloc(sizeof(bool));
}

void	in_file_init(t_group	**info, char *s, char *name)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	printf("substr in|%s|\n", name);
	free(name);
	if (s[1] == '<')
		new->here_doc = 1;
	else
		new->here_doc = 0;
	new->next = NULL;
	lstaddback(&(*info)->infile, new);
	// printf("ll test %s", (*info)->infile->name);
}

void	out_file_init(t_group	**info, char *s, char *name)
{
	t_outfile	*new;

	new = malloc(sizeof(t_outfile));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	printf("substr out|%s|\n", new->name);
	free(name);
	if (s[1] == '<')
		new->append = 1;
	else
		new->append = 0;
	new->next = NULL;

	lstaddback_out(&(*info)->outfile, new); //how do i make it in one function? 
	// printf("ll test out %s", (*info)->outfile->name);
}

void	words_init(t_group	**info, char *name)
{
	t_command	*new;
	t_command	*head;

	head = (*info)->word;
	new = malloc(sizeof(t_command));
	if (!new)
		return ;
	new->word = name;
	printf("substr word|%s|\n", new->word);
	// new->next = NULL;
	// while ((*info)->word->next)
	// 	(*info)->word = (*info)->word->next;
	// (*info)->word->next = new;
	// (*info)->word = head;
}
