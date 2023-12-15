/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 19:32:31 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_get_cmd(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	if (!valid_builtin(cmd->argv[0]))
	{
		cmd_path = ft_which(cmd->argv[0], envp);
		if (cmd_path)
		{
			free(cmd->argv[0]);
			cmd->argv[0] = cmd_path;
		}
		else
		{
			command_not_found(cmd);
			cmd->exit_code = 127;
		}
	}
}

static void	_exec(t_list *command, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*cmd_next;
	t_bool	create_pipe;
	int		pipefd[2];

	cmd = command->data;
	cmd_next = NULL;
	if (command->next)
		cmd_next = command->next->data;
	create_pipe = (cmd_next && cmd->fd_out == cmd_next->fd_in);
	if (valid_builtin(cmd->argv[0]))
	{
		pipefd[1] = cmd->fd_out;
		if (create_pipe)
		{
			pipe(pipefd);
			cmd->fd_out = pipefd[0];
		}
		cmd->exit_code = handle_builtins(cmd->argv, pipefd[1]);
	}
	else
		cmd->pid = ft_execve(&cmd->fd_in, cmd->argv, envp, &cmd->fd_out);
	if (create_pipe)
		cmd_next->fd_in = cmd->fd_out;
	ft_close(&cmd->fd_in);
}

static void	_command_execution(t_list *command, char **envp)
{
	t_cmd	*cmd;
	int		status;

	if (command)
	{
		cmd = command->data;
		_get_cmd(cmd, envp);
		_exec(command, envp);
		_command_execution(command->next, envp);
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
			if (init_cmd_list_fd(cmd_list))
				ft_last_exit_code(EXIT_FAILURE);
			else
			{
				_command_execution(cmd_list->cmd, envp);
				ft_last_exit_code(((t_cmd *)
						ft_lstlast(cmd_list->cmd)->data)->exit_code);
			}
		}
		previous_control = cmd_list->control;
		command_line = command_line->next;
	}
}

void	execution(t_list *command_line)
{
	char	**envp;

	get_envp_tab(&envp);
	ft_last_exit_code(EXIT_SUCCESS);
	_command_line_execution(command_line, envp);
	free(envp);
}
