/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:11:06 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/11 18:26:18 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strjoinnfree(char **s1, char *s2)
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

int	matches(char *s, char *match)
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
			++j;
			while (++i && i < slen && j < matchlen && s[i] != match[j])
				;
		}
		if (s[i] != match[j])
			return (0);
		++i;
		++j;
	}
	return (s[i] == 0);
}

char	*glob(char *match)
{
	char			*pwd;
	DIR				*dir;
	char			*result;
	char			*file;
	struct dirent	*dirent;

	if (ft_strchr(match, '/') && ft_strchr(match, '*'))
		return (NULL);
	result = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	dir = opendir(pwd);
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		file = dirent->d_name;
		if (matches(file, match))
		{
			if (result)
				ft_strjoinnfree(&result, " ");
			ft_strjoinnfree(&result, file);
		}
	}
	free(pwd);
	closedir(dir);
	return (result);
}
