/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 17:43:58 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **argv)
{
	char	**parts;

	if (*argv == NULL)
		return (builtin_env(argv));
	while (*argv)
	{
		parts = ft_split(*argv, "=");
		if (parts == NULL)
			return (0);
		if (parts[1] == NULL)
		{
			++argv;
			ft_split_free(parts);
			continue ;
		}
		ft_setenv(*argv++);
		ft_split_free(parts);
	}
	return (1);
}
