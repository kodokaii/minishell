/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 03:06:53 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_exit_code(int exit_code)
{
	static int	last_exit_code = 0;

	if (exit_code == -1)
		return (last_exit_code);
	last_exit_code = exit_code;
	return (last_exit_code);
}

void	command_not_found(t_cmd *cmd)
{
	ft_dprintf(STDERR_FILENO, PROGRAM_NAME": command not found: %s\n",
		cmd->argv[0]);
	cmd->fd_in = INVALID_FD;
	cmd->fd_out = INVALID_FD;
}
