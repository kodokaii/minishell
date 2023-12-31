/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:32:01 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 18:35:16 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	process_cmd(t_list **token_list, t_cmd *cmd)
{
	t_token	*token;
	size_t	i;

	i = 0;
	init_cmd(cmd, *token_list);
	while (*token_list)
	{
		token = (*token_list)->data;
		if (is_control_type(token->type))
			break ;
		if (token->type == TOKEN_WORD)
			cmd->argv[i++] = ft_strdup(token->data);
		if (token->type == TOKEN_SUBSHELL)
		{
			cmd->argv[0] = ft_strdup(ft_argv(NULL)[0]);
			cmd->argv[1] = ft_strdup(token->data);
			i = 2;
		}
		check_files(token, cmd);
		*token_list = (*token_list)->next;
	}
	if (i == 0)
		cmd->argv[i++] = ft_strdup("cat");
	cmd->argv[i] = 0;
}

static void	process_cmd_list(t_list **token_list, t_list **cmds)
{
	t_cmd	*cmd;
	t_token	*token;

	*cmds = NULL;
	while (*token_list)
	{
		cmd = malloc(sizeof(t_cmd));
		process_cmd(token_list, cmd);
		ft_lstadd_back(cmds, ft_lstnew(cmd));
		if (*token_list)
		{
			token = (*token_list)->data;
			if (token->type == TOKEN_AND
				|| token->type == TOKEN_OR)
				break ;
			*token_list = (*token_list)->next;
		}
	}
}

static void	process_command_line(t_list *token_list, t_list **command_line)
{
	t_cmd_list	*cmd_list;
	t_token		*token;

	while (token_list)
	{
		cmd_list = malloc(sizeof(t_cmd_list));
		process_cmd_list(&token_list, &cmd_list->cmd);
		ft_lstadd_back(command_line, ft_lstnew(cmd_list));
		if (token_list)
		{
			token = token_list->data;
			if (token->type == TOKEN_AND)
				cmd_list->control = CONTROL_AND;
			else if (token->type == TOKEN_OR)
				cmd_list->control = CONTROL_OR;
			token_list = token_list->next;
		}
		else
			cmd_list->control = CONTROL_NONE;
	}
}

t_list	*parse(char *str)
{
	t_list	*token_list;
	t_list	*command_line;

	command_line = NULL;
	lexing(str, &token_list);
	if (!token_error(token_list))
		process_command_line(token_list, &command_line);
	ft_lstclear(&token_list, free_token);
	return (command_line);
}
