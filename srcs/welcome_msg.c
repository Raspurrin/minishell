/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:29:41 by mialbert          #+#    #+#             */
/*   Updated: 2022/11/30 12:09:10 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shlvl_msg(t_env *envp_head, bool exit)
{
	const t_env	*env = find_node(envp_head, "SHLVL");
	char		*lvl;
	char		*lvl2;

	if (!env)
	{
		ft_printf_fd(STDERR_FILENO, "\033[0;34mShell level has been unset. By you. Thanks.\n"
		"Who knows where we are now\n\033[0m");
		return ;
		}
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
	ft_printf_fd(STDERR_FILENO, "\033[1;35mWelcome to the"
		"Minishell queens': %s \n\n"
		"               T~~\n"
		"               |\n"
		"              /\"\\\n"
		"      T~~     |\'| T~~\n"
		"  T~~ |    T~ WWWW|\n"
		"  |  /\'\\   |  |  |/\\T~~\n"
		" /\"\\ WWW  /\"\\ |\' |WW|\n"
		"WWWWW/\\| /   \\|\'/\\|/\"\\\n"
		"|   /__\\/|WWW|\\/__\\WWWW\n"
		"|\"  WWWW\'|I_I|\'WWWW\'  |\n"
		"|   |\' |/  -  \\|\' |\'  |\n"
		"|\'  |  |LI=H=LI|\' |   |\n"
		"|   |\' | |[_]| |  |\'  |\n"
		"|   |  |_|###|_|  |   |\n"
		"\'---\'--\'-/___\\-\'--\'---\'\n", PROMPT);
	shlvl_msg(envp_head, false);
}
