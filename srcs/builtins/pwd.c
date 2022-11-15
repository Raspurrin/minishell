
#include "../../includes/minishell.h"

void	init_pwd(t_data *data)
{
	t_env	*lst;

	lst = find_node(data->envp_head, "PWD");
	data->pwd = lst->value;
}

void	pwd(t_data *data, t_group *group)
{
	(void)group;
	if (!data->pwd)
		init_pwd(data);
	printf("%s\n", data->pwd);
}
