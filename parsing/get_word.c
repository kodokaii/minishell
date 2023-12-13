/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 02:27:20 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_add_char(t_buf *word, size_t *word_size, char c, t_quote quote)
{
	if ((c != '\'' && c != '\"') || quote != QUOTE_NONE)
	{
		ft_buf_write(word, (t_buf[1]){{&c, 1}}, *word_size);
		(*word_size)++;
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

char	*get_word(t_str_quoted *str_quoted)
{
	t_buf	word;		
	size_t	word_size;

	word_size = 0;
	forward_char(str_quoted, count_blank(get_str(str_quoted)));
	ft_bzero(&word, sizeof(t_buf));
	while (_in_word(get_str(str_quoted), *get_quote(str_quoted)))
	{
		if (get_quote(str_quoted)[0] != QUOTE_SINGLE
			&& get_str(str_quoted)[0] == '$')
			fill_env(str_quoted);
		else
		{
			_add_char(&word, &word_size,
				*get_str(str_quoted), *get_quote(str_quoted));
			forward_char(str_quoted, 1);
		}
	}
	_add_char(&word, &word_size, '\0', QUOTE_NONE);
	return (word.buf);
}
