/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:41:20 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/14 22:18:49 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token(t_token *token)
{
	ft_printf("%p\n", token);
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

void	print_command_line(t_list *command_line)
{
	size_t	i;
	t_list	*cmd;

	while (command_line)
	{
		cmd = ((t_cmd_list *)command_line->data)->cmd;
		while (cmd)
		{
			i = 0;
			while (((t_cmd *)cmd->data)->argv[i])
				ft_printf("(%s) ", ((t_cmd *)cmd->data)->argv[i++]);
			ft_printf("-> ");
			cmd = cmd->next;
		}
		ft_printf("\n");
		command_line = command_line->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	ft_printf("argv: ");
	while (cmd->argv[i])
		ft_printf("%s ", cmd->argv[i++]);
	ft_printf("\nfd in: %d\nfd out: %d\n", cmd->fd_in, cmd->fd_out);
}
