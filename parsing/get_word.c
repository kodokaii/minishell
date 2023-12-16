/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/16 03:26:40 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_char(t_word *word, char c, t_quote quote)
{
	if ((c != '\'' && c != '\"') || quote != QUOTE_NONE)
	{
		ft_buf_write(&word->str, (t_buf[1]){{&c, sizeof(c)}},
			word->size * sizeof(c));
		ft_buf_write(&word->quote, (t_buf[1]){{&quote, sizeof(quote)}},
			word->size * sizeof(quote));
		word->size++;
	}
}

static t_bool	_in_word(char *str, t_quote quote)
{
	if (str[0])
	{
		if (quote != QUOTE_NONE)
			return (FT_TRUE);
		if (get_token_type(str) == TOKEN_WORD)
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

static t_bool	_in_env(char *str, t_quote *quote)
{
	return (quote[0] != QUOTE_SINGLE && quote[1] != QUOTE_SINGLE
		&& str[0] == '$'
		&& (ft_isalnum(str[1]) || str[1] == '_'));
}

char	*get_word(t_str_quoted *str_quoted)
{
	t_word	word;

	ft_bzero(&word, sizeof(t_word));
	forward_char(str_quoted, count_blank(get_str(str_quoted)));
	if (!get_str(str_quoted)[0])
		return (ft_strdup(END_LINE));
	while (_in_word(get_str(str_quoted), *get_quote(str_quoted)))
	{
		if (_in_env(get_str(str_quoted), get_quote(str_quoted)))
			fill_env(str_quoted);
		else
		{
			_add_char(&word, *get_str(str_quoted), *get_quote(str_quoted));
			forward_char(str_quoted, 1);
		}
	}
	_add_char(&word, '\0', QUOTE_NONE);
	fill_glob(str_quoted, &word);
	ft_buf_free(&word.quote);
	return (word.str.buf);
}
