/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:59:17 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FT_FALSE);
		++i;
	}
	return (FT_TRUE);
}

int	builtin_export(char **argv, int fd)
{
	char	**parts;
	int		exit_code;

	if (*argv == NULL)
		return (builtin_env(argv, fd));
	exit_code = 1;
	while (*argv)
	{
		parts = ft_split(*argv, "=");
		if (parts == NULL)
			return (0);
		if (!is_valid_name(*parts))
			ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": export: invalid variable name\n");
		if (parts[1] == NULL || !is_valid_name(*parts))
		{
			++argv;
			ft_split_free(parts);
			continue ;
		}
		ft_setenv(*argv++);
		ft_split_free(parts);
		exit_code = 0;
	}
	return (ft_close(&fd), (!exit_code));
}
