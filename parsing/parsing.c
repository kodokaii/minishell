/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:32:01 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/14 03:08:27 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
		ft_printf("(WORD: \"%s\")", token->data);
	if (token->type == TOKEN_AND)
		ft_printf("(AND)");
	if (token->type == TOKEN_OR)
		ft_printf("(OR)");
	if (token->type == TOKEN_PIPE)
		ft_printf("(PIPE)");
	if (token->type == TOKEN_IO_IN)
		ft_printf("(IN: \"%s\")", token->data);
	if (token->type == TOKEN_IO_HEREDOC)
		ft_printf("(HEREDOC: \"%s\")", token->data);
	if (token->type == TOKEN_IO_OUT)
		ft_printf("(OUT: \"%s\")", token->data);
	if (token->type == TOKEN_IO_APPEND)
		ft_printf("(APPEND: \"%s\")", token->data);
	if (token->type == TOKEN_SUBSHELL)
		ft_printf("(SUBSHELL: \"%s\")", token->data);
	if (token->type == TOKEN_ERROR)
		ft_printf("(ERROR: \"%s\")", token->data);
}

static void	open_fds(t_token *token, t_cmd *cmd)
{
	int	fd;

	if (token->type == TOKEN_IO_OUT && cmd->fd_in != FD_ERRORED)
	{
		fd = reporting_open(token->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		cmd->fd_out = FD_ERRORED;
		if (fd > 0)
			cmd->fd_out = fd;
	}
	else if (token->type == TOKEN_IO_IN && cmd->fd_out != FD_ERRORED)
	{
		fd = reporting_open(token->data, O_RDONLY, 0);
		cmd->fd_in = FD_ERRORED;
		if (fd > 0)
			cmd->fd_in = fd;
	}
	else if (token->type == TOKEN_IO_APPEND && cmd->fd_in != FD_ERRORED)
	{
		fd = reporting_open(token->data, O_CREAT | O_APPEND, 0644);
		cmd->fd_out = FD_ERRORED;
		if (fd > 0)
			cmd->fd_out = fd;
	}
}

static void	process_cmd(t_list **token_list, t_list **command_line)
{
	t_cmd	*cmd;
	t_token	*token;
	size_t	i;

	i = 0;
	cmd = init_cmd(*token_list);
	while (*token_list)
	{
		token = (*token_list)->data;
		if (token->type == TOKEN_WORD)
			cmd->argv[i++] = ft_strdup(token->data);
		open_fds(token, cmd);
		*token_list = (*token_list)->next;
	}
	cmd->argv[i] = 0;
	if (*command_line == NULL && cmd->fd_in == FD_UNSET)
		cmd->fd_in = STDIN_FILENO;
	if (*token_list == NULL && cmd->fd_out == FD_UNSET)
		cmd->fd_out = STDOUT_FILENO;
	ft_lstadd_back(command_line, ft_lstnew(cmd));
}

static void	process_tokens(t_list *token_list, t_list **command_line)
{
	while (token_list)
	{
		process_cmd(&token_list, command_line);
		if (token_list)
			token_list = token_list->next;
	}
}

t_list	*parse(char *str)
{
	t_list	*token_list;
	t_list	*command_line;

	command_line = NULL;
	lexing(str, &token_list);
	if (!token_error(token_list))
		process_tokens(token_list, &command_line);
	ft_putlst_fd(token_list, &print_token, STDOUT_FILENO);
	write(1, "\n", 1);
	ft_lstclear(&token_list, free_token);
	return (command_line);
}
