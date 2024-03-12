/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:52:35 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 20:19:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	any_command_active(int whether)
{
	static int	value = 0;

	if (whether >= 0)
		value = whether;
	return (value);
}

static void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		if (any_command_active(-1))
			ft_putchar_fd('\n', 1);
		else
		{
			ft_putchar_fd('\n', 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signal == SIGQUIT)
		ft_putstr_fd("\b\b \b  \b\b", STDOUT_FILENO);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
