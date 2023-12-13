/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 03:08:42 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*_get_meta(t_str_quoted	*str_quoted, size_t size)
{
	char	*str;

	str = get_str(str_quoted);
	forward_char(str_quoted, size);
	return (ft_strndup(str, size));
}

static char	*_get_next_word(t_str_quoted *str_quoted, size_t offset)
{
	forward_char(str_quoted, offset);
	return (get_word(str_quoted));
}

static char	*get_subshell(t_str_quoted *str_quoted)
{
	t_uint	bracket_count;
	char	*str;
	size_t	i;

	i = 0;
	bracket_count = 1;
	str = get_str(str_quoted) + 1;
	while (str[i] && bracket_count)
	{
		if (str[i] == '(')
			bracket_count++;
		if (str[i] == ')')
			bracket_count--;
		if (bracket_count)
			i++;
	}
	forward_char(str_quoted, i + 2);
	return (ft_strndup(str, i));
}

void	get_token(t_str_quoted	*str_quoted, t_token *token)
{
	token->type = get_token_type(get_str(str_quoted));
	if (token->type == TOKEN_AND)
		token->data = _get_meta(str_quoted, 2);
	else if (token->type == TOKEN_OR)
		token->data = _get_meta(str_quoted, 2);
	else if (token->type == TOKEN_PIPE)
		token->data = _get_meta(str_quoted, 1);
	else if (token->type == TOKEN_IO_HEREDOC)
		token->data = _get_next_word(str_quoted, 2);
	else if (token->type == TOKEN_IO_APPEND)
		token->data = _get_next_word(str_quoted, 2);
	else if (token->type == TOKEN_IO_IN)
		token->data = _get_next_word(str_quoted, 1);
	else if (token->type == TOKEN_IO_OUT)
		token->data = _get_next_word(str_quoted, 1);
	else if (token->type == TOKEN_SUBSHELL)
		token->data = get_subshell(str_quoted);
	else if (token->type == TOKEN_WORD)
		token->data = get_word(str_quoted);
	else
		token->data = _get_meta(str_quoted, 1);
}
