/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/14 03:16:53 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	_is_error(t_token *token, t_token_type last_type)
{
	if (token->type == TOKEN_ERROR)
		return (FT_TRUE);
	if (is_control_type(token->type) && is_control_type(last_type))
		return (FT_TRUE);
	return (FT_FALSE);
}

t_bool	token_error(t_list	*token_list)
{
	t_token_type	last_type;

	last_type = TOKEN_PIPE;
	while (token_list)
	{
		if (_is_error(token_list->data, last_type))
		{
			syntax_error(token_list->data);
			return (FT_TRUE);
		}
		last_type = ((t_token *)token_list->data)->type;
		token_list = token_list->next;
	}
	return (FT_FALSE);
}
