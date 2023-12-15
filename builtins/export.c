/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 20:09:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_valid_name(char *str, size_t name_len)
{
	size_t	i;

	i = 0;
	if (str == NULL || *str == '=')
		return (FT_FALSE);
	while (i < name_len && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FT_FALSE);
		++i;
	}
	return (FT_TRUE);
}

int	builtin_export(char **argv, int fd)
{
	size_t	name_len;
	int		exit_code;

	exit_code = 0;
	if (*argv == NULL)
		return (builtin_env(argv, fd));
	while (*argv)
	{
		name_len = 0;
		while ((*argv)[name_len] && (*argv)[name_len] != '=')
			name_len++;
		if (!(*argv)[name_len])
			exit_code = 1;
		else if (is_valid_name(*argv, name_len))
			ft_setenv(*argv);
		else
		{
			ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": export: invalid variable name\n");
			exit_code = 1;
		}
		argv++;
	}
	return (ft_close(&fd), exit_code);
}
