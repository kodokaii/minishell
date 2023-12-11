/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:11:06 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/11 20:17:32 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strjoinnfree(char **s1, char *s2)
{
	char	*tmp;

	if (*s1 == NULL)
	{
		*s1 = ft_strdup(s2);
		return ;
	}
	tmp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = tmp;
}

static int	matches(char *s, char *match)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	size_t	matchlen;

	if (*s == '.' && *match != '.')
		return (0);
	i = 0;
	j = 0;
	slen = ft_strlen(s) + 1;
	matchlen = ft_strlen(match) + 1;
	while (i < slen && j < matchlen)
	{
		if (match[j] == '*')
		{
			while (match[j] == '*')
				++j;
			while (i < slen && j < matchlen && s[i] != match[j])
				++i;
		}
		if (s[i++] != match[j++])
			return (0);
	}
	return (s[i] == 0);
}

static t_should_continue	glob_impl(DIR *dir, char *match, char **result)
{
	struct dirent	*dirent;
	char			*file;

	dirent = readdir(dir);
	if (dirent == NULL)
		return (SHOULD_NOT_CONTINUE);
	file = dirent->d_name;
	if (matches(file, match))
	{
		if (*result)
			ft_strjoinnfree(result, " ");
		ft_strjoinnfree(result, file);
	}
	return (SHOULD_CONTINUE);
}

char	*glob(char *match)
{
	char			*pwd;
	DIR				*dir;
	char			*result;

	if (ft_strchr(match, '/') && ft_strchr(match, '*'))
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
