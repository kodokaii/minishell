/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 17:53:52 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_token(t_token *token)
{
	free(token->data);
	free(token);
}

void	free_cmd(t_cmd *cmd)
{
	ft_split_free(cmd->argv);
	ft_lstclear(&cmd->files_in, free);
	ft_lstclear(&cmd->files_out, free);
	free(cmd);
}

void	free_cmd_list(t_cmd_list *cmd_list)
{
	ft_lstclear(&cmd_list->cmd, free_cmd);
	free(cmd_list);
}
