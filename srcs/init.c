/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:46:32 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/09 01:43:01 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_path(t_data *data, char **envp)
{
	char	*tmp;

	while (*envp != NULL)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
		{
			data->paths = ft_split(*envp, ':');
			tmp = ft_substr(data->paths[0], 5, \
							ft_strlen(data->paths[0]) - 5);
			free (data->paths[0]);
			data->paths[0] = tmp;
		}
		envp++;
		data->envpc++;
	}
	return ;
}

void	init_env(t_data *data, char **envp)
{
	char	**tmp;
	t_env	*lst;

	data->envp_head = malloc(sizeof(t_env));
	lst = data->envp_head;
	while (*envp != NULL)
	{
		lst->keyvalue = *envp;
		tmp = ft_split(*envp, '=');
		lst->key = tmp[0];
		lst->value = tmp[1];
		envp++;
		if (*envp != NULL)
		{
			lst->next = malloc(sizeof(t_env));
			lst = lst->next;
		}
	}
	lst->next = NULL;
	// lst = data->envp_head;
	// printf("--------------\n");
	// while (lst->next != NULL)
	// {
	// 	printf("hi: %s\n", lst->keyvalue);
	// 	lst = lst->next;
	// }
	// lst->next = malloc(sizeof(t_env));
	// lst->next->keyvalue = "something=else";
	// lst->next->key = "something";
	// lst->next->value = "else";
	// lst->next->next = NULL;
	// printf("--------------\n");
	// lst = data->envp_head;
	// while (lst != NULL)
	// {
	// 	printf("ha: %s\n", lst->keyvalue);				<- this worked lol
	// 	lst = lst->next;
	// }
	// ------------------------------------------------
	// lst = malloc(sizeof(t_env));
	// lst->keyvalue = ft_strdup("yo");
	// lst->next = NULL;
	// lst = data->envp_head;
	// printf("--------------\n");
	// while (lst != NULL)
	// {
	// 	printf("wot: %s\n", lst->keyvalue);
	// 	lst = lst->next;
	// }
	// lst->next = NULL; // this didn't suffice somehow I needed ft_calloc to prevent segfault?
	/** wtf log: 
	 * first lst->next = NULL didn't work, I had to add ft_calloc in the while loop
	 * And then instead I tried to change calloc to malloc and added lst = NULL which didn't work
	 * but then both lst = NULL and lst->next = NULL DID work
	 * And then I changed it back to only lst->next = NULL and now that works... Somehow. Wtf.
	 * 
	 * Note to self: segv with linked lists usually happens because of not having a NULL pointer somewhere
	 */
}

void	init(t_data *data, char **envp)
{
	init_path(data, envp);
	init_env(data, envp);
	init_pwd(data);
}
