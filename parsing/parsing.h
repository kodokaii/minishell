/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 01:44:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_ERROR,
	TOKEN_WORD,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_IO_IN,
	TOKEN_IO_HEREDOC,
	TOKEN_IO_OUT,
	TOKEN_IO_APPEND,
	TOKEN_SUBSHELL
}	t_token_type;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
}	t_quote;

typedef struct s_str_quoted
{
	char	*str;
	t_quote	*quote;
	size_t	index;
}	t_str_quoted;

typedef struct t_token
{
	t_token_type	type;
	char			*data;
}	t_token;

int				parsing(char *str);

void			str_quoted_init(char *str, t_str_quoted *str_quoted);
void			parse_str_quoted(char *str, t_str_quoted *str_quoted);
t_str_quoted	str_quoted_join(t_str_quoted *str_quoted1,
					t_str_quoted *str_quoted2);

void			lexing(char *str, t_list **token_lst);
void			get_token(t_str_quoted *str_quoted, t_token *token);
char			*get_word(t_str_quoted *str_quoted);

void			fill_env(t_str_quoted *str_quoted);

t_token_type	get_token_type(char *str);
char			*skip_blank(char *str);
size_t			count_blank(char *str);

char			*get_str(t_str_quoted *str_quoted);
t_quote			*get_quote(t_str_quoted *str_quoted);
void			forward_char(t_str_quoted *str_quoted, size_t i);
void			free_str_quoted(t_str_quoted *str_quoted);

void			free_token(t_token *token);

#endif
