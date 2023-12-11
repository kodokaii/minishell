/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/10 21:22:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type	get_token_type(char *str)
{
	if (str[0] == '&' && str[1] == '&')
		return (TOKEN_AND);
	if (str[0] == '|' && str[1] == '|')
		return (TOKEN_OR);
	if (str[0] == '>' && str[1] == '>')
		return (TOKEN_IO_APPEND);
	if (str[0] == '<' && str[1] == '<')
		return (TOKEN_IO_HEREDOC);
	if (str[0] == '|')
		return (TOKEN_PIPE);
	if (str[0] == '>')
		return (TOKEN_IO_OUT);
	if (str[0] == '<')
		return (TOKEN_IO_IN);
	if (str[0] == '(')
		return (TOKEN_SUBSHELL);
	if (ft_isprint(str[0]) && !ft_isspace(str[0]) && str[0] != ')')
		return (TOKEN_WORD);
	return (TOKEN_ERROR);
}

char	*skip_blank(char *str)
{
	while (*str && ft_strchr(" \t", *str))
		str++;
	return (str);
}

t_bool	in_word(char *str, t_quote *quote)
{
	if (str[0])
	{
		if (*quote == QUOTE_SINGLE && str[0] != '\'')
			return (FT_TRUE);
		if (*quote == QUOTE_DOUBLE && str[0] != '\"')
			return (FT_TRUE);
		if (str[0] == '\'' || str[0] == '\"')
			return (FT_FALSE);
		return (get_token_type(str) == TOKEN_WORD);
	}
	return (FT_FALSE);
}

t_bool	in_bracket(char *str)
{
	return (str[0] && str[0] != ')');
}
