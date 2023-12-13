/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quoted_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 03:01:51 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_str(t_str_quoted *str_quoted)
{
	return (str_quoted->str + str_quoted->index);
}

t_quote	*get_quote(t_str_quoted *str_quoted)
{
	return (str_quoted->quote + str_quoted->index);
}

void	forward_char(t_str_quoted *str_quoted, size_t i)
{
	while (i-- && str_quoted->str[str_quoted->index])
		str_quoted->index += 1;
}

void	free_str_quoted(t_str_quoted *str_quoted)
{
	free(str_quoted->str);
	free(str_quoted->quote);
}
