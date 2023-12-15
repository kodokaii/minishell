/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:27 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:07:17 by cgodard          ###   ########.fr       */
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

static int	varcmp(char *s1, char *s2)
{
	size_t	name1len;
	size_t	name2len;

	name1len = 0;
	while (s1[name1len] && s1[name1len] != '=')
		++name1len;
	name2len = 0;
	while (s2[name2len] && s2[name2len] != '=')
		++name2len;
	return (name1len == name2len
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

char	*ft_getenv(char *name)
{
	t_list	*envp;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(ft_last_exit_code(-1)));
	envp = *ft_envp(NULL);
	while (envp && !varcmp((char *)envp->data, name))
		envp = envp->next;
	if (!envp)
		return (NULL);
	return (ft_strchr((char *)envp->data, '=') + 1);
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
