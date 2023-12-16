/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/16 02:34:19 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	_get_env_len(char *str)
{
	size_t	len;

	len = 0;
	if (!str[0] || str[0] == '?')
		return (1);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

static char	*_get_env(t_str_quoted *str_quoted)
{
	char	*env;
	char	*path;
	size_t	path_len;

	if (!get_str(str_quoted)[0] || ft_isspace(get_str(str_quoted)[0]))
		return ("$");
	path_len = _get_env_len(get_str(str_quoted));
	path = ft_strndup(get_str(str_quoted), path_len);
	env = ft_getenv(path);
	if (!env)
		env = "";
	free(path);
	forward_char(str_quoted, path_len);
	return (env);
}

static void	_fill_quote(t_str_quoted *env_quoted, t_quote quote)
{
	size_t	i;

	i = 0;
	while (env_quoted->str[i])
	{
		if (ft_isblank(env_quoted->str[i]) && quote == QUOTE_NONE)
			env_quoted->quote[i] = QUOTE_NONE;
		else
			env_quoted->quote[i] = QUOTE_SINGLE;
		i++;
	}
}

void	fill_env(t_str_quoted *str_quoted)
{
	t_str_quoted	env_quoted;
	t_str_quoted	new_str_quoted;
	t_quote			quote;
	char			*env;

	quote = *get_quote(str_quoted);
	forward_char(str_quoted, 1);
	env = _get_env(str_quoted);
	if (quote == QUOTE_NONE)
		env = skip_blank(env);
	str_quoted_init(env, &env_quoted);
	_fill_quote(&env_quoted, quote);
	new_str_quoted = str_quoted_join(&env_quoted, str_quoted);
	free_str_quoted(&env_quoted);
	free_str_quoted(str_quoted);
	*str_quoted = new_str_quoted;
}
