/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 00:47:51 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	_is_error(t_list *token_list, t_token_type last_type)
{
	t_token	*token;

	token = token_list->data;
	if (token->type == TOKEN_ERROR)
		return (FT_TRUE);
	if (is_control_type(token->type)
		&& (is_control_type(last_type) || !token_list->next))
		return (FT_TRUE);
	if ((token->type == TOKEN_WORD || token->type == TOKEN_SUBSHELL)
		&& last_type == TOKEN_SUBSHELL)
		return (FT_TRUE);
	if ((token->type == TOKEN_IO_IN || token->type == TOKEN_IO_HEREDOC
			|| token->type == TOKEN_IO_OUT || token->type == TOKEN_IO_APPEND)
		&& !ft_strcmp(token->data, END_LINE))
		return (FT_TRUE);
	return (FT_FALSE);
}

t_bool	token_error(t_list	*token_list)
{
	t_token_type	last_type;

	last_type = TOKEN_PIPE;
	while (token_list)
	{
		if (_is_error(token_list, last_type))
		{
			syntax_error(token_list->data);
			return (FT_TRUE);
		}
		last_type = ((t_token *)token_list->data)->type;
		token_list = token_list->next;
	}
	return (FT_FALSE);
}
