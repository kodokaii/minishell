/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/13 23:23:51 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	all_file_size(t_list *file_lst)
{
	size_t	size;

	size = 0;
	while (file_lst)
	{
		size += ft_strlen(file_lst->data);
		file_lst = file_lst->next;
		if (file_lst)
			size++;
	}
	return (size);
}

static void	_fill_word(t_word *word, t_list	*first_file)
{
	size_t	size;

	ft_buf_free(&word->str);
	ft_buf_free(&word->quote);
	size = ft_strlen(first_file->data) + 1;
	word->str.buf = ft_strdup(first_file->data);
	word->str.size = size;
	word->quote.buf = malloc(size * sizeof(t_quote));
	word->quote.size = size * sizeof(t_quote);
	word->size = size;
	while (size--)
		((t_quote *)word->quote.buf)[size] = QUOTE_SINGLE;
}

static void	_add_file(t_str_quoted *file_quoted, char *file)
{
	char	*str;
	t_quote	*quote;
	size_t	i;

	i = 0;
	quote = get_quote(file_quoted);
	str = get_str(file_quoted);
	ft_strcpy(str, file);
	while (file[i])
		quote[i++] = QUOTE_SINGLE;
	forward_char(file_quoted, i);
}

static void	_get_file_quoted(t_str_quoted *file_quoted, t_list *file_lst)
{
	size_t	size;

	file_quoted->index = 0;
	size = all_file_size(file_lst);
	file_quoted->str = malloc(size + 1);
	file_quoted->quote = malloc((size + 1) * sizeof(t_quote));
	while (file_lst)
	{
		_add_file(file_quoted, file_lst->data);
		file_lst = file_lst->next;
		if (file_lst)
		{
			get_str(file_quoted)[0] = ' ';
			get_quote(file_quoted)[0] = QUOTE_NONE;
			forward_char(file_quoted, 1);
		}
	}
	file_quoted->index = 0;
}

void	fill_glob(t_str_quoted *str_quoted, t_word *word)
{
	t_str_quoted	file_quoted;
	t_str_quoted	new_str_quoted;
	t_list			*file_lst;

	file_lst = get_glob((t_str_quoted[1]){{word->str.buf, word->quote.buf, 0}});
	if (file_lst)
	{
		_fill_word(word, file_lst);
		if (file_lst->next)
		{
			_get_file_quoted(&file_quoted, file_lst->next);
			new_str_quoted = str_quoted_join(&file_quoted, str_quoted);
			free_str_quoted(&file_quoted);
			free_str_quoted(str_quoted);
			*str_quoted = new_str_quoted;
		}
	}
	ft_lstclear(&file_lst, free);
}
