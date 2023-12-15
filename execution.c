/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 03:21:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_get_envp_tab(char ***envp_tab)
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

static void	_get_cmd(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = ft_which(cmd->argv[0], envp);
	if (cmd_path)
	{
		free(cmd->argv[0]);
		cmd->argv[0] = cmd_path;
	}
	else
		command_not_found(cmd);
}

static void	_command_execution(t_list *command, char **envp)
{
	t_cmd	*cmd;
	int		status;

	if (command)
	{
		cmd = command->data;
		_get_cmd(cmd, envp);
		if (command->next)
		{
			cmd->fd_out = INVALID_FD;
			cmd->pid = ft_execve(&cmd->fd_in, cmd->argv, envp, &cmd->fd_out);
			((t_cmd *)command->next->data)->fd_in = cmd->fd_out;
			_command_execution(command->next, envp);
		}
		else
			cmd->pid = ft_execve(&cmd->fd_in, cmd->argv, envp, &cmd->fd_out);
		if (cmd->pid != INVALID_PID)
		{
			waitpid(cmd->pid, &status, 0);
			cmd->exit_code = WEXITSTATUS(status);
		}
	}
}

static void	_command_line_execution(t_list *command_line, char **envp)
{
	t_cmd_list	*cmd_list;
	t_control	previous_control;

	previous_control = CONTROL_NONE;
	while (command_line)
	{
		cmd_list = command_line->data;
		if (previous_control == CONTROL_NONE
			|| (previous_control == CONTROL_AND && !ft_last_exit_code(-1))
			|| (previous_control == CONTROL_OR && ft_last_exit_code(-1)))
		{
			_command_execution(cmd_list->cmd, envp);
			cmd_list->exit_code
				= ((t_cmd *)ft_lstlast(cmd_list->cmd)->data)->exit_code;
			ft_last_exit_code(cmd_list->exit_code);
		}
		previous_control = cmd_list->control;
		command_line = command_line->next;
	}
}

void	execution(t_list *command_line)
{
	char	**envp;

	_get_envp_tab(&envp);
	ft_last_exit_code(EXIT_SUCCESS);
	_command_line_execution(command_line, envp);
	free(envp);
}
