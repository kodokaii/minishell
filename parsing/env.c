/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/10 23:11:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	get_env_len(char *str)
{
	size_t	len;

	len = 0;
	if (str[0] == '?')
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

static int	get_env(char *str, char **env)
{
	char	*env_static;
	char	*path;
	size_t	path_len;

	*env = NULL;
	path_len = get_env_len(str);
	path = strndup(str, path_len);
	if (!path)
		return (EXIT_FAILURE);
	env_static = getenv(path);
	free(path);
	if (!env_static)
		return (EXIT_SUCCESS);
	*env = strdup(env_static);
	if (!env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_env_list(char *str, t_list **env_list, size_t *len)
{
	t_list	*env_elem;
	char	*env;
	size_t	i;

	i = 0;
	*len = 0;
	*env_list = NULL;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (get_env(str + i, &env))
				return (EXIT_FAILURE);
			i += get_env_len(str + i);
			env_elem = ft_lstnew(env);
			if (!env_elem)
				return (free(env), EXIT_FAILURE);
			ft_lstadd_back(env_list, env_elem);
			if (env)
				*len += ft_strlen(env);
		}
		else
			(*len)++;
	}
	return (EXIT_SUCCESS);
}

void	env_cpy(char *str_env, char *str, t_list *env_list)
{
	t_list	*current;
	size_t	i;

	i = 0;
	current = env_list;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (current->data)
			{
				ft_strcpy(str_env + i, current->data);
				i += ft_strlen(current->data);
			}
			str += get_env_len(str);
			current = current->next;
		}
		else
			str_env[i++] = *(str++);
	}
	str_env[i] = '\0';
}

char	*fill_env(char *str)
{
	t_list	*env_list;
	char	*str_env;
	size_t	len;

	if (get_env_list(str, &env_list, &len))
		return (ft_lstclear(&env_list, free), NULL);
	str_env = malloc(len + 1);
	if (!str_env)
		return (NULL);
	env_cpy(str_env, str, env_list);
	ft_lstclear(&env_list, free);
	return (str_env);
}
