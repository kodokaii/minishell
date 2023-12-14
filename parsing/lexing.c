/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/14 02:41:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexing(char *str, t_list **token_lst)
{
	t_token			*token;
	t_str_quoted	str_quoted;

	*token_lst = NULL;
	parse_str_quoted(str, &str_quoted);
	while (get_str(&str_quoted)[0])
	{
		token = malloc(sizeof(t_token));
		get_token(&str_quoted, token);
		ft_lstadd_back(token_lst, ft_lstnew(token));
		forward_char(&str_quoted, count_blank(get_str(&str_quoted)));
	}
	free_str_quoted(&str_quoted);
}
