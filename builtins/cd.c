/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:58:18 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/08 14:13:57 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **argv)
{
	char	*dir;

	if (*argv == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
			return (ft_dprintf(STDERR_FILENO,
					PROGRAM_NAME": cd: missing $HOME\n"), 0);
	}
	else if (argv[1] != NULL)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": cd: too many arguments\n"), 0);
	else
		dir = *argv;
	if (chdir(dir) < 0)
		return (ft_dprintf(STDERR_FILENO, PROGRAM_NAME": cd: %s: %s\n",
				*argv, strerror(errno)), 0);
	return (1);
}
