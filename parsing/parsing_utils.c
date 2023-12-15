/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 01:01:00 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:51:42 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	is_control_type(t_token_type type)
{
	return (type == TOKEN_AND
		|| type == TOKEN_OR
		|| type == TOKEN_PIPE);
}

void	reporting_open(char *filename, int flags, int mode, int *fd)
{
	int	myfd;

	myfd = open(filename, flags, mode);
	*fd = INVALID_FD;
	if (myfd < 0)
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME": %s: %s\n",
			filename, strerror(errno));
	}
	else
		*fd = myfd;
}

size_t	count_words_in_command(t_list *command_line)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (command_line)
	{
		token = command_line->data;
		if (token->type == TOKEN_SUBSHELL)
		{
			i = 2;
			break ;
		}
		if (is_control_type(token->type))
			break ;
		if (token->type == TOKEN_WORD)
			++i;
		command_line = command_line->next;
	}
	if (i == 0)
		i = 1;
	return (i);
}

void	syntax_error(t_token *token)
{
	ft_putstr_fd(PROGRAM_NAME": syntax error near unexpected token",
		STDERR_FILENO);
	if (token->data)
	{
		if (ft_strcmp(token->data, END_LINE))
			ft_dprintf(STDERR_FILENO, " '%s'", token->data);
		else
			ft_dprintf(STDERR_FILENO, " 'newline'", token->data);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_cmd(t_cmd *cmd, t_list *token_list)
{
	cmd->argv = malloc((count_words_in_command(token_list) + 1)
			* sizeof(char *));
	cmd->fd_in = STDIN_FILENO;
	cmd->pid = INVALID_PID;
	cmd->exit_code = 0;
	cmd->fd_out = STDOUT_FILENO;
}
