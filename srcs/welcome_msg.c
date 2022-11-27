/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:29:41 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/22 18:33:11 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shlvl_msg(t_env *envp_head, bool exit)
{
	const t_env	*env = find_node(envp_head, "SHLVL");
	char		*lvl;
	char		*lvl2;

	lvl = env->value;
	if (exit && lvl)
		lvl2 = ft_itoa(ft_atoi(lvl) - 1);
	else
		lvl2 = ft_strdup(env->value);
	if (ft_strcmp(lvl2, "1") == 0)
		ft_printf_fd(STDERR_FILENO, "\033[0;31mYEET (╯°□°）╯︵ [you]\n");
	else
		ft_printf_fd(STDERR_FILENO, "\033[0;34m You are at shell level: "
			"%s🤿\n", lvl2);
	ft_printf_fd(STDERR_FILENO, "\033[0m");
	free(lvl2);
}

void	greeting_msg(t_env *envp_head)
{
	ft_printf_fd(STDERR_FILENO, "\033[1;35m    Welcome to 🦇MiShell\n\n"
		"    /\\                 /\\\n"
		"   / \\'._   (\\_/)   _.'/ \\\n "
		" /_.''._'--('.')--'_.''._\\ \n"
		"  | \\_ / `;=/ \" \\=;` \\ _/ |\n"
		"   \\/ `\\__|`\\___/`|__/` \\/\n"
		"           \\(/|\\)/ \n      "
		"      \"   \"\n\033[0m");
	shlvl_msg(envp_head, false);
}
