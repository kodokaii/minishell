/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:57:10 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 18:14:53 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define HEREDOC_TMP_FILE "/tmp/minishell_heredoc"

int	ft_heredoc(char *delim)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_TMP_FILE, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (INVALID_FD);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, delim) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	ft_close(&fd);
	fd = open(HEREDOC_TMP_FILE, O_RDONLY);
	unlink(HEREDOC_TMP_FILE);
	return (fd);
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

int	reporting_open(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME": %s: %s\n",
			filename, strerror(errno));
	return (fd);
}

int	open_file(t_file *file)
{
	if (file->type == OUTPUT)
		return (reporting_open(
				file->name, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (file->type == INPUT)
		return (reporting_open(file->name, O_RDONLY, 0));
	else if (file->type == APPEND)
		return (reporting_open(file->name, O_CREAT | O_APPEND, 0644));
	else if (file->type == TOKEN_IO_HEREDOC)
		return (ft_heredoc(file->name));
	return (-1);
}
