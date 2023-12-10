/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/10 23:01:10 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*init_quote(char *str, t_quote *quote)
{
	*quote = QUOTE_NONE;
	if (str[0] == '\'' || str[0] == '\"')
	{
		if (str[0] == '\'')
			*quote = QUOTE_SINGLE;
		else
			*quote = QUOTE_DOUBLE;
		return (str + 1);
	}
	return (str);
}

static char	*get_word(char *str, t_token *token)
{
	t_quote	quote;
	char	*with_env;
	size_t	i;

	i = 0;
	str = init_quote(str, &quote);
	while (in_word(str + i, &quote))
		i++;
	token->data = ft_strndup(str, i);
	if (!token->data)
		return (NULL);
	if (quote != QUOTE_SINGLE)
	{
		with_env = fill_env(token->data);
		free(token->data);
		if (!with_env)
			return (NULL);
		token->data = with_env;
	}
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	return (str + i);
}

static char	*get_subshell(char *str, t_token *token)
{
	size_t	i;

	i = 0;
	while (in_bracket(str + i))
		i++;
	token->data = ft_strndup(str, i);
	if (!token->data)
		return (NULL);
	if (str[i])
		i++;
	return (str + i);
}

static char	*get_error(char *str, t_token *token)
{
	token->data = ft_strndup(str, 1);
	if (!token->data)
		return (NULL);
	return (str + 1);
}

char	*get_token(char *str, t_token *token)
{
	token->data = NULL;
	token->type = get_token_type(str);
	if (token->type == TOKEN_AND)
		return (str + 2);
	if (token->type == TOKEN_OR)
		return (str + 2);
	if (token->type == TOKEN_PIPE)
		return (str + 1);
	if (token->type == TOKEN_IO_HEREDOC)
		return (get_word(skip_blank(str + 2), token));
	if (token->type == TOKEN_IO_APPEND)
		return (get_word(skip_blank(str + 2), token));
	if (token->type == TOKEN_IO_IN)
		return (get_word(skip_blank(str + 1), token));
	if (token->type == TOKEN_IO_OUT)
		return (get_word(skip_blank(str + 1), token));
	if (token->type == TOKEN_SUBSHELL)
		return (get_subshell(str + 1, token));
	if (token->type == TOKEN_WORD)
		return (get_word(str, token));
	return (get_error(str, token));
}
