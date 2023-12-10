/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/10 20:28:48 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	add_token(t_list **token_lst, t_token *token)
{
	void	*data;
	t_list	*token_elem;

	data = ft_memdup(token, sizeof(t_token));
	if (!data)
		return (EXIT_FAILURE);
	token_elem = ft_lstnew(data);
	if (!token_elem)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(token_lst, token_elem);
	return (EXIT_SUCCESS);
}

int	lexing(char *str, t_list **token_lst)
{
	t_token	token;

	*token_lst = NULL;
	str = skip_blank(str);
	while (*str)
	{
		str = get_token(str, &token);
		if (!str)
			return (ft_lstclear(token_lst, free_token), EXIT_FAILURE);
		if (add_token(token_lst, &token))
			return (ft_lstclear(token_lst, free_token), EXIT_FAILURE);
		str = skip_blank(str);
	}
	return (EXIT_SUCCESS);
}
