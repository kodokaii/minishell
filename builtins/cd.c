/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:58:18 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:59:38 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **argv, int fd)
{
	char	*dir;

	if (*argv == NULL)
	{
		dir = ft_getenv("HOME");
		if (dir == NULL)
			return (ft_close(&fd), ft_dprintf(STDERR_FILENO,
					PROGRAM_NAME": cd: missing $HOME\n"), 1);
	}
	else if (argv[1] != NULL)
		return (ft_close(&fd), ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": cd: too many arguments\n"), 1);
	else
		dir = *argv;
	if (chdir(dir) < 0)
		return (ft_close(&fd),
			ft_dprintf(STDERR_FILENO, PROGRAM_NAME": cd: %s: %s\n",
				*argv, strerror(errno)), 1);
	return (ft_close(&fd), 0);
}
