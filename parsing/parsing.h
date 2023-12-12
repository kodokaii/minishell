/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/12 19:13:40 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_IO_IN,
	TOKEN_IO_HEREDOC,
	TOKEN_IO_OUT,
	TOKEN_IO_APPEND,
	TOKEN_SUBSHELL,
	TOKEN_ERROR,
}	t_token_type;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
}	t_quote;

typedef struct t_token
{
	t_token_type	type;
	char			*data;
}	t_token;

typedef struct s_cmd
{
	int		fd_in;
	char	**argv;
	pid_t	pid;
	int		exit_code;
	int		fd_out;
}			t_cmd;

int				parsing(char *str);

int				lexing(char *str, t_list **token_lst);
char			*get_token(char *str, t_token *token);

char			*fill_env(char *str);

t_token_type	get_token_type(char *str);
char			*skip_blank(char *str);
t_bool			in_word(char *str, t_quote *quote);
t_bool			in_bracket(char *str);

void			free_token(t_token *token);
void			free_cmd(t_cmd *cmd);

#endif
