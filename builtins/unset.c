/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 03:57:12 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, int fd)
{
	if (*argv == NULL)
		return (ft_close(&fd), ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": unset: not enough arguments\n",
				strerror(errno)), 1);
	while (*argv)
		ft_unsetenv(*argv++);
	ft_close(&fd);
	return (0);
}
