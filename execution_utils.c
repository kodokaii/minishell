/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 03:29:53 by nlaerema         ###   ########.fr       */
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

void	get_envp_tab(char ***envp_tab)
{
	t_list	*envp_list;
	size_t	size;
	size_t	i;

	i = 0;
	envp_list = *ft_envp(NULL);
	size = ft_lstsize(envp_list);
	*envp_tab = malloc((size + 1) * sizeof(void *));
	while (envp_list)
	{
		(*envp_tab)[i] = envp_list->data;
		envp_list = envp_list->next;
		i++;
	}
	(*envp_tab)[i] = NULL;
}
