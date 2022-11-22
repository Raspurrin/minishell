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
	t_env	*env;
	char	*lvl;

	env = find_node(envp_head, "SHLVL");
	lvl = env->value;
	if (exit)
		lvl = ft_itoa(ft_atoi(lvl) - 1); // free?
	ft_printf_fd(STDERR_FILENO, "\033[0;34m You are at shell level: "
		"%s🤿\n\033[0m", lvl);
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
"      \"   \"\n");
	shlvl_msg(envp_head, false);
}
