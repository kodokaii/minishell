/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/12 19:13:00 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	syntax_error(t_token *token)
{
	ft_putstr_fd(PROGRAM_NAME": invalid token!!!!!!!!!!!!", STDERR_FILENO);
	if (token->data)
		ft_dprintf(STDERR_FILENO,
			" (%s)", token->data);
	ft_putchar_fd('\n', STDERR_FILENO);
}

static int	is_command_separator_command(t_token *token)
{
	return (token->type == TOKEN_AND
		|| token->type == TOKEN_OR
		|| token->type == TOKEN_PIPE);
}

static size_t	count_words_in_command(t_list *command_line)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (command_line)
	{
		token = command_line->data;
		if (is_command_separator_command(token))
			break ;
		if (token->type == TOKEN_WORD)
			++i;
		command_line = command_line->next;
	}
	return (i);
}

static void	print_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	ft_printf("argv: ");
	while (cmd->argv[i])
		ft_printf("%s ", cmd->argv[i++]);
	ft_printf("\nfd in: %d\nfd out: %d\n", cmd->fd_in, cmd->fd_out);
}

static void	open_fds(t_token *token, t_cmd *cmd)
{
	int	fd;

	if (token->type == TOKEN_IO_OUT)
	{
		fd = open(token->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		cmd->fd_out = fd;
	}
	else if (token->type == TOKEN_IO_IN)
	{
		fd = open(token->data, O_RDONLY);
		cmd->fd_in = fd;
	}
	else if (token->type == TOKEN_IO_APPEND)
	{
		fd = open(token->data, O_CREAT | O_APPEND, 0644);
		cmd->fd_in = fd;
	}
}

static void	process_cmd(t_list **token_list, t_list **command_line)
{
	t_cmd	*cmd;
	char	**argv;
	t_token	*token;
	size_t	i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	argv = malloc((count_words_in_command((*token_list)) + 1) * sizeof(char *));
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->argv = argv;
	while (*token_list)
	{
		token = (*token_list)->data;
		if ((*token_list) && is_command_separator_command(token))
			break ;
		if (token->type == TOKEN_WORD)
			argv[i++] = token->data;
		open_fds(token, cmd);
		*token_list = (*token_list)->next;
	}
	argv[i] = 0;
	if (*command_line == NULL)
		cmd->fd_in = STDIN_FILENO;
	ft_lstadd_back(command_line, ft_lstnew(cmd));
	if (token_list == NULL)
		cmd->fd_out = STDOUT_FILENO;
}

static int	any_error(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->data;
		if (token->type == TOKEN_ERROR)
		{
			syntax_error(token);
			return (1);
		}
		token_list = token_list->next;
	}
	return (0);
}

static void	process_tokens(t_list *token_list, t_list **command_line)
{
	while (token_list)
	{
		if (*command_line == NULL
			&& is_command_separator_command(token_list->data))
		{
			syntax_error(token_list->data);
			break ;
		}
		process_cmd(&token_list, command_line);
		if (token_list)
			token_list = token_list->next;
	}
}

int	parsing(char *str)
{
	t_list	*token_list;
	t_list	*command_line;

	if (lexing(str, &token_list) || any_error(token_list))
		return (ft_lstclear(&token_list, free_token), EXIT_FAILURE);
	command_line = NULL;
	process_tokens(token_list, &command_line);
	ft_putlst_fd(command_line, print_cmd, STDOUT_FILENO);
	ft_lstclear(&token_list, free_token);
	ft_lstclear(&command_line, free_cmd);
	return (EXIT_SUCCESS);
}
