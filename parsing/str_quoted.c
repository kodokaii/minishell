/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quoted.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 02:48:23 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	_update_quote(char c, t_quote *quote)
{
	if (c == '\'' && *quote == QUOTE_NONE)
		*quote = QUOTE_SINGLE;
	else if (c == '\"' && *quote == QUOTE_NONE)
		*quote = QUOTE_DOUBLE;
	else if ((c == '\'' && *quote == QUOTE_SINGLE)
		|| (c == '\"' && *quote == QUOTE_DOUBLE))
		*quote = QUOTE_NONE;
}

void	str_quoted_init(char *str, t_str_quoted *str_quoted)
{
	str_quoted->str = ft_strdup(str);
	str_quoted->quote = malloc((ft_strlen(str_quoted->str) + 1)
			* sizeof(t_quote));
	str_quoted->index = 0;
}

void	parse_str_quoted(char *str, t_str_quoted *str_quoted)
{
	t_quote		quote;
	size_t		i;

	i = 0;
	quote = QUOTE_NONE;
	str_quoted_init(skip_blank(str), str_quoted);
	while (str_quoted->str[i])
	{
		str_quoted->quote[i] = quote;
		_update_quote(str_quoted->str[i], &quote);
		if (quote == QUOTE_NONE)
			str_quoted->quote[i] = QUOTE_NONE;
		i++;
	}
	str_quoted->quote[i] = QUOTE_NONE;
}

t_str_quoted	str_quoted_join(t_str_quoted *str_quoted1,
					t_str_quoted *str_quoted2)
{
	t_str_quoted	str_quoted_dst;
	char			*new_str;
	size_t			len1;
	size_t			len2;

	len1 = ft_strlen(get_str(str_quoted1));
	len2 = ft_strlen(get_str(str_quoted2));
	new_str = ft_strjoin(get_str(str_quoted1), get_str(str_quoted2));
	str_quoted_init(new_str, &str_quoted_dst);
	ft_memcpy(get_quote(&str_quoted_dst), get_quote(str_quoted1),
		len1 * sizeof(t_quote));
	ft_memcpy(get_quote(&str_quoted_dst) + len1, get_quote(str_quoted2),
		len2 * sizeof(t_quote));
	return (str_quoted_dst);
}
