/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:54:11 by pooneh            #+#    #+#             */
/*   Updated: 2022/11/03 21:37:03 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

void	print_linkedlist(t_token *data)
{
	t_token	*tmp;
	size_t	i;

	tmp = data;
	i = 0;
	while (tmp->next != NULL)
	{
		printf("i: %zu   element:%c\n", i, tmp->infile->name[0]);
		tmp = tmp->next;
	}
}
/*test comment */
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
	while (s[i] && (s[i] == ' ' || s[i] == '\t'
			|| s[i] == '\n'))
		i++;
	return (i);
}
