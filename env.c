/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:27 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 19:03:26 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ft_envp(char **envp)
{
	static char	**saved_envp = NULL;
	size_t		i;

	if (envp == NULL)
		return (&saved_envp);
	i = 0;
	while (envp[i])
		++i;
	saved_envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		saved_envp[i] = ft_strdup(envp[i]);
		++i;
	}
	saved_envp[i] = NULL;
	return (NULL);
}

void	ft_unsetenv(char *name)
{
	char	**envp;
	char	**parts;
	size_t	i;
	size_t	j;

	i = 0;
	envp = *ft_envp(NULL);
	while (envp[i])
	{
		parts = ft_split(envp[i], "=");
		if (ft_strcmp(*parts, name) == 0)
		{
			j = 0;
			while (envp[j])
				++j;
			envp[i] = envp[j - 1];
			envp[j - 1] = NULL;
		}
		ft_split_free(parts);
		++i;
	}
}

static int	varcmp(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2,
			ft_strchr(s1, '=') - s1) == 0);
}

void	ft_setenv(char *variable)
{
	char	***envp;
	int		replace;
	size_t	i;

	envp = ft_envp(NULL);
	replace = -1;
	i = 0;
	while ((*envp)[i])
	{
		if (varcmp((*envp)[i], variable))
			replace = i;
		++i;
	}
	if (replace >= 0)
	{
		free((*envp)[replace]);
		(*envp)[replace] = variable;
	}
	else
	{
		*envp = ft_realloc(*envp,
				(i + 1) * sizeof(char *), (i + 2) * sizeof(char *));
		(*envp)[i] = variable;
		(*envp)[i + 1] = NULL;
	}
}
