/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:11:06 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/13 15:27:52 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	matches(char *s, t_str_quoted *match)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	size_t	matchlen;

	if (*s == '.' && *match->str != '.')
		return (0);
	i = 0;
	j = 0;
	slen = ft_strlen(s) + 1;
	matchlen = ft_strlen(match->str) + 1;
	while (i < slen && j < matchlen)
	{
		if (match->str[j] == '*' && match->quote[j] == QUOTE_NONE)
		{
			while (match->str[j] == '*' && match->quote[j] == QUOTE_NONE)
				++j;
			while (i < slen && j < matchlen && s[i] != match->str[j])
				++i;
		}
		if (s[i++] != match->str[j++])
			return (0);
	}
	return (s[i] == 0);
}

static t_should_continue	glob_impl(
	DIR *dir, t_str_quoted *match, t_list **result)
{
	struct dirent	*dirent;
	char			*file;

	dirent = readdir(dir);
	if (dirent == NULL)
		return (SHOULD_NOT_CONTINUE);
	file = dirent->d_name;
	if (matches(file, match))
		ft_lstadd_back(result, ft_lstnew(file));
	return (SHOULD_CONTINUE);
}

t_list	*glob(t_str_quoted *match)
{
	char	*pwd;
	DIR		*dir;
	t_list	*result;

	if (ft_strchr(match->str, '/') && ft_strchr(match->str, '*'))
		return (NULL);
	result = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	dir = opendir(pwd);
	if (dir == NULL)
		return (NULL);
	while (1)
		if (!glob_impl(dir, match, &result))
			break ;
	free(pwd);
	closedir(dir);
	return (result);
}
