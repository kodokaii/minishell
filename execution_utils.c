/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/16 03:51:38 by nlaerema         ###   ########.fr       */
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

static int	_get_redirection(t_cmd *cmd)
{
	t_list	*current;

	current = cmd->files_in;
	while (current)
	{
		cmd->fd_in = open_file(current->data);
		if (cmd->fd_in == INVALID_FD)
			return (EXIT_FAILURE);
		current = current->next;
	}
	current = cmd->files_out;
	while (current)
	{
		cmd->fd_out = open_file(current->data);
		if (cmd->fd_out == INVALID_FD)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	init_cmd_list_fd(t_cmd_list *cmd_list)
{
	t_list	*current;

	current = cmd_list->cmd;
	if (current)
		((t_cmd *)current->data)->fd_in = STDIN_FILENO;
	while (current)
	{
		if (!current->next)
			((t_cmd *)current->data)->fd_out = STDOUT_FILENO;
		if (_get_redirection(current->data))
			((t_cmd *)current->data)->exit_code = 1;
		current = current->next;
	}
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
