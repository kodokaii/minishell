/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/11 15:09:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_token(t_token *token)
{
	if (token->type == TOKEN_WORD)
		ft_printf("(WORD: \"%s\")", token->data);
	if (token->type == TOKEN_AND)
		ft_printf("(AND)");
	if (token->type == TOKEN_OR)
		ft_printf("(OR)");
	if (token->type == TOKEN_PIPE)
		ft_printf("(PIPE)");
	if (token->type == TOKEN_IO_IN)
		ft_printf("(IN: \"%s\")", token->data);
	if (token->type == TOKEN_IO_HEREDOC)
		ft_printf("(HEREDOC: \"%s\")", token->data);
	if (token->type == TOKEN_IO_OUT)
		ft_printf("(OUT: \"%s\")", token->data);
	if (token->type == TOKEN_IO_APPEND)
		ft_printf("(APPEND: \"%s\")", token->data);
	if (token->type == TOKEN_SUBSHELL)
		ft_printf("(SUBSHELL: \"%s\")", token->data);
	if (token->type == TOKEN_ERROR)
		ft_printf("(ERROR: \"%s\")", token->data);
}

int	parsing(char *str)
{
	t_list	*token_list;

	if (lexing(str, &token_list))
	{
		ft_printf("Error !\n");
		return (EXIT_FAILURE);
	}
	ft_putlst_fd(token_list, print_token, STDOUT_FILENO);
	ft_printf("\n");
	ft_lstclear(&token_list, free_token);
	return (EXIT_SUCCESS);
}
