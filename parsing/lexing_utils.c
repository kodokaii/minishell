/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/12 23:17:54 by nlaerema         ###   ########.fr       */
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
	while (*str && ft_isblank(*str))
		str++;
	return (str);
}

size_t	count_blank(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && ft_isblank(str[count]))
		count++;
	return (count);
}
