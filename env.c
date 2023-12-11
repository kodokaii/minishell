/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:27 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/11 15:14:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**ft_envp(char **envp)
{
	static t_list	*saved_envp = NULL;
	size_t			i;

	if (envp == NULL)
		return (&saved_envp);
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&saved_envp, ft_lstnew(ft_strdup(envp[i])));
		++i;
	}
	return (NULL);
}

static size_t	indexof(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		++i;
	}
	return (i);
}

static int	varcmp(char *s1, char *s2)
{
	return (indexof(s1, '=') == indexof(s2, '=')
		&& ft_strncmp(s1, s2, ft_strchr(s1, '=') - s1) == 0);
}

void	ft_unsetenv(char *name)
{
	t_list	**envp;

	envp = ft_envp(NULL);
	while (*envp && !varcmp((char *)(*envp)->data, name))
		envp = &(*envp)->next;
	ft_lstremove(envp, free);
}

void	ft_setenv(char *variable)
{
	t_list	*envp;
	int		replaced;

	envp = *ft_envp(NULL);
	replaced = 0;
	while (envp)
	{
		if (varcmp((char *)envp->data, variable))
		{
			replaced = 1;
			free(envp->data);
			envp->data = ft_strdup(variable);
		}
		envp = envp->next;
	}
	if (!replaced)
		ft_lstadd_back(ft_envp(NULL), ft_lstnew(ft_strdup(variable)));
}
