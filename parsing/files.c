/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:57:10 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 17:57:11 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define HEREDOC_TMP_FILE "/tmp/minishell_heredoc"

void	ft_heredoc(char *delim, int *fd)
{
	char	*line;
	int		myfd;

	myfd = open(HEREDOC_TMP_FILE, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (myfd < 0)
	{
		*fd = INVALID_FD;
		return ;
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, delim) == 0)
			break ;
		ft_putstr_fd(line, myfd);
		ft_putchar_fd('\n', myfd);
		free(line);
	}
	ft_close(&myfd);
	*fd = open(HEREDOC_TMP_FILE, O_RDONLY);
	unlink(HEREDOC_TMP_FILE);
}

void	check_files(t_token *token, t_cmd *cmd)
{
	t_file	*file;

	if (token->type == TOKEN_IO_OUT)
	{
		file = malloc(sizeof(t_file));
		file->name = token->data;
		file->type = OUTPUT;
		ft_lstadd_back(&cmd->files_out, ft_lstnew(file));
	}
	else if (token->type == TOKEN_IO_IN)
	{
		file = malloc(sizeof(t_file));
		file->name = token->data;
		file->type = INPUT;
		ft_lstadd_back(&cmd->files_in, ft_lstnew(file));
	}
	else if (token->type == TOKEN_IO_APPEND)
	{
		file = malloc(sizeof(t_file));
		file->name = token->data;
		file->type = APPEND;
		ft_lstadd_back(&cmd->files_out, ft_lstnew(file));
	}
	else if (token->type == TOKEN_IO_HEREDOC)
	{
		file = malloc(sizeof(t_file));
		file->name = NULL;
		file->type = HEREDOC;
		ft_lstadd_back(&cmd->files_in, ft_lstnew(file));
	}
}

/*
void	open_fds(t_token *token, t_cmd *cmd)
{
	if (token->type == TOKEN_IO_OUT && cmd->fd_in != INVALID_FD)
		reporting_open(
			token->data, O_CREAT | O_TRUNC | O_WRONLY, 0644, &cmd->fd_out);
	else if (token->type == TOKEN_IO_IN && cmd->fd_out != INVALID_FD)
		reporting_open(token->data, O_RDONLY, 0, &cmd->fd_in);
	else if (token->type == TOKEN_IO_APPEND && cmd->fd_in != INVALID_FD)
		reporting_open(token->data, O_CREAT | O_APPEND, 0644, &cmd->fd_out);
	else if (token->type == TOKEN_IO_HEREDOC && cmd->fd_out != INVALID_FD)
		ft_heredoc(token->data, &cmd->fd_in);
}
*/
