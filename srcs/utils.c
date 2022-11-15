
#include "../includes/minishell.h"

void	lstclear(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = (t_env *)lst;
	while (tmp != NULL)
	{
		tmp = (tmp)->next;
		free(lst->keyvalue);
		free(lst->key);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	tmp = NULL;
}

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	free_2d_guard(&data->paths);
	lstclear((void *)data->envp_head);
	free(data->pwd);
	while (i < data->groupc)
	{
		free_2d_guard(&data->group[i].full_cmd);
		// lstclear((void *)data->group[i].outfile);
		// lstclear((void *)data->group[i].infile);
		i++;
	}
}

size_t	get_lstsize(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env	*find_node(t_env *lst, char *key)
{
	while (lst != NULL)
	{
		if (ft_strncmp(lst->key, key, ft_strlen(lst->key)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	**env_2darr(t_data *data, t_env *lst)
{
	char	**env;
	size_t	i;

	i = 0;
	if (!lst)
		return (display_error(data, "Env list failed to create", true), NULL);
	env = malloc((get_lstsize(data->envp_head) + 1) * sizeof(char *)); // count size each time
	while (lst->next != NULL)
	{
		env[i] = ft_strdup(lst->keyvalue);
		// printf("env: %s\n", env[i]);
		lst = lst->next;
		i++;
	}
	// printf("env[i]: %s\n", env[i]);
	// printf("env[i - 1]: %s\n", env[i - 1]);
	env[i] = NULL;
	// i = 0;
	// while (env[i])
	// 	ft_printf_fd(STDOUT_FILENO, "%s\n", env[i++]);
	return (env);
}